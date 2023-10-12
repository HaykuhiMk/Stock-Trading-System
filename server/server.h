#ifndef SERVER_H
#define SERVER_H

#include "conf.h"
#include "orderBook.h"
#include "archivedOrder.h"
#include "limitArchivedOrder.h"
#include "marketArchivedOrder.h"
#include "..\src\trader.h"
#include "..\src\limitTrader.h"
#include "..\src\marketTrader.h"
#include "..\src\order.h"
#include "..\src\stock.h"
#include "..\src\marketOrder.h"
#include "..\src\limitOrder.h"

#include <string>

class Server {
public:
    Server();
    ~Server();

public:
    void saveOrder(const std::string& message);
    void run();
    void initOrderBook();
    OrderBook& getOrderBook();
    void saveReceivedMessage(const std::string& message);
    std::string getReceivedMessage();
    void deserializeOrderFromString();

private:
    SOCKET serverSocket;
    struct addrinfo serverAddr;
    OrderBook orderBook;
    std::mutex messageMutex;
    std::string receivedMessage;
};

#endif  //SERVER_H

