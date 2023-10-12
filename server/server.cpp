#include "server.h"

#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <limits>

Server::Server() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        std::cerr << "Failed to initialize!" << std::endl;
        exit(EXIT_FAILURE);
    }
#endif  // _WIN32

    struct addrinfo hints, *bindAddress;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(nullptr, "8080", &hints, &bindAddress);
    serverSocket = socket(bindAddress->ai_family, bindAddress->ai_socktype, bindAddress->ai_protocol);
    if (serverSocket == -1) {
        perror("Error creating socket!");
        exit(EXIT_FAILURE);
    }
    if (bind(serverSocket, bindAddress->ai_addr, bindAddress->ai_addrlen)) {
        perror("Error binding!");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(bindAddress);
    std::cout << "Server is initialized and bound to port 8080." << std::endl;
}

Server::~Server() {
    CLOSESOCKET(serverSocket);
#ifdef _WIN32
    WSACleanup();
#endif  //_WIN32
    std::cout << "Server is shutting down." << std::endl;
}

OrderBook& Server::getOrderBook() {
    return orderBook;
}

void Server::saveOrder(const std::string& message) {
    saveReceivedMessage(message);
    deserializeOrderFromString();
}

void Server::run() {
    if (listen(serverSocket, 10) < 0) {
        perror("Error listening!");
        exit(EXIT_FAILURE);
    }
    fd_set master, reads;
    FD_ZERO(&master);
    FD_SET(serverSocket, &master);
    int maxSocket = serverSocket;
    initOrderBook();
    std::cout << "Server is listening for incoming connections..." << std::endl;
    while (true) {
        reads = master;
        if (select(maxSocket + 1, &reads, nullptr, nullptr, nullptr) < 0) {
            perror("Error selecting!");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i <= maxSocket; ++i) {
            if (FD_ISSET(i, &reads)) {
                if (i == serverSocket) {
                    struct sockaddr_storage clientAddress;
                    socklen_t clientLen = sizeof(clientAddress);
                    int socketClient = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
                    if (socketClient == -1) {
                        perror("Error accepting!");
                        exit(EXIT_FAILURE);
                    }
                    FD_SET(socketClient, &master);
                    if (socketClient > maxSocket) {
                        maxSocket = socketClient;
                    }
                    char addressBuffer[NI_MAXHOST];
                    getnameinfo((struct sockaddr*)&clientAddress, clientLen, addressBuffer, sizeof(addressBuffer), 0, 0, NI_NUMERICHOST);
                    std::cout << "New connection from " << addressBuffer << std::endl;
                } else {
                    std::string read;
                    read.resize(1024);  
                    int bytesReceived = recv(i, &read[0], 1024, 0);
                    if (bytesReceived <= 0) {
                        FD_CLR(i, &master);
                        CLOSESOCKET(i);
                    } else {
                        read.resize(bytesReceived); 
                        saveOrder(read);
                        for (int j = 0; j <= maxSocket; ++j) {
                            if (FD_ISSET(j, &master) && j != serverSocket && j != i) {
                                send(j, read.c_str(), bytesReceived, 0);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Server::initOrderBook() {
    std::ofstream stockFile("stocks.txt", std::ios::app);  // Open a file for writing
    if (!stockFile.is_open()) {
        std::cerr << "Failed to open the stocks file for writing." << std::endl;
        return;
    }
    while (true) {
        std::cout << "Creation of shares: " << std::endl;
        int stockID;
        double price;
        int count;
        std::cout << "Enter Stock ID: ";
        std::cin >> stockID;
        std::cout << "Enter Stock price: ";
        std::cin >> price;
        std::cout << "Enter Order Quantity: ";
        std::cin >> count;
#ifdef max
#pragma push_macro("max")
#undef max
#define _restore_max_
#endif
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#ifdef _restore_max_
#pragma pop_macro("max")
#undef _restore_max_
#endif
        Stock stock(stockID, price, count);
        this->orderBook.addStock(&stock);
        stockFile << "Stock ID: " << stock.getID() << ", Price: " << stock.getPrice() << ", Count: " << stock.getCount() << "\n";
        std::cout << "Enter any symbol if you want to create shares or 'quit' to exit. " << std::endl;
        std::string message;
        std::getline(std::cin, message);
        if (message == "quit") {
            break;
        }
    }
    stockFile.close();  
    if (stockFile.fail()) {
        std::cerr << "Failed to close the stocks file." << std::endl;
    }
}


void Server::saveReceivedMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(messageMutex);
    receivedMessage = message;
}

std::string Server::getReceivedMessage() {
    std::lock_guard<std::mutex> lock(messageMutex);
    return receivedMessage;
}

void Server::deserializeOrderFromString() {
    std::istringstream ss(getReceivedMessage());
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    if (tokens.size() < 5) {
        std::cerr << "Invalid serialized Order data: " << receivedMessage << std::endl;
        return;
    }
    std::string orderType = tokens.back();
    tokens.pop_back(); 
    int orderID = std::stoi(tokens[0]);
    int traderID = std::stoi(tokens[1]);
    int stockID = std::stoi(tokens[2]);
    int orderCount = std::stoi(tokens[3]);
    Order* newOrder = nullptr;
    if (orderType == "LimitOrder") {
        if (tokens.size() == 5) {
            double price = std::stod(tokens[4]);
            ArchivedOrder* newArchivedLimitOrder = new LimitArchivedOrder(orderID, traderID, stockID, orderCount, price);
            orderBook.addOrder(newArchivedLimitOrder);
        } else {
            std::cerr << "Invalid serialized LimitOrder data: " << receivedMessage << std::endl;
        }
    } else if (orderType == "MarketOrder") {
        ArchivedOrder* newArchivedLimitOrder = new MarketArchivedOrder(orderID, traderID, stockID, orderCount);
        orderBook.addOrder(newArchivedLimitOrder);
    } else {
        std::cerr << "Unknown order type: " << orderType << std::endl;
    }
}

