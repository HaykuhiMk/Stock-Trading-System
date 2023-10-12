#include "client.h"

#include <iostream>
#include <cstring>

Client::Client() : serverIP("127.0.0.1"), serverPort(8080), clientSocket(-1), trader(nullptr) {}

Client::~Client() {
    disconnectFromServer();
}

void Client::selectTraderType() {
    char type;
    int traderID = 0;
    double balance = 0;
    std::cout << "Select your trader type (0 for LimitTrader, 1 for MarketTrader): ";
    std::cin >> type;
    std::cout << "Enter Trader ID: ";
    std::cin >> traderID;
    std::cout << "Enter Trader balance: ";
    std::cin >> balance;
    if (type == '0') {
        this->trader = new LimitTrader(traderID, balance);
        this->trader->setType(type);
        std::cout << "From now on You are Limit Trader." << std::endl;
    } else if (type == '1') {
        this->trader = new MarketTrader(traderID, balance);
        this->trader->setType(type);
        std::cout << "From now on You are Market Trader." << std::endl;
    } else {
        throw std::invalid_argument("Invalid trader type parameter.");
    }
}

void Client::connectToServer() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        std::cerr << "Failed to initialize Winsock!" << std::endl;
        exit(EXIT_FAILURE);
    }
#endif
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
#ifdef _WIN32
    serverAddress.sin_addr.s_addr = inet_addr(serverIP);
    if (serverAddress.sin_addr.s_addr == INADDR_NONE) {
        perror("Invalid server IP address");
        exit(EXIT_FAILURE);
    }
#else
    if (inet_pton(AF_INET, serverIP, &(serverAddress.sin_addr)) <= 0) {
        perror("Invalid server IP address");
        exit(EXIT_FAILURE);
    }
#endif
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
}

void Client::disconnectFromServer() {
    if (clientSocket != -1) {
#ifdef _WIN32
        closesocket(clientSocket);
        WSACleanup();
#else
        close(clientSocket);
#endif
        clientSocket = -1;
    }
}

void Client::sendMessage(const std::string& message) {
    if (clientSocket == -1) {
        std::cerr << "Not connected to the server." << std::endl;
        return;
    }
    if (send(clientSocket, message.c_str(), message.size(), 0) == -1) {
        perror("Error sending data");
        disconnectFromServer();
    }
}

void Client::clientCreateOrder() {
    int stockID = 0;
    std::cout << "Enter Stock ID: ";
    std::cin >> stockID;
    Stock stock;
    stock.loadStockFromID(stockID);
    std::string message = trader->createOrder(&stock);
    sendMessage(message);
}

void Client::displayMenu() {
    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1 - Create Order" << std::endl;
        std::cout << "2 - Exit" << std::endl;
        int choice;
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice)) {
            std::cerr << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
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
        }
        switch (choice) {
            case 1:
                clientCreateOrder();
                break;
            case 2:
                std::cout << "Exiting server menu." << std::endl;
                return;  
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
}
