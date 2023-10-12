#ifndef CLIENT_H
#define CLIENT_H

#include "conf.h"
#include "..\src\trader.h"
#include "..\src\limitTrader.h"
#include "..\src\marketTrader.h"
#include "..\src\order.h"
#include "..\src\stock.h"
#include "..\src\marketOrder.h"
#include "..\src\limitOrder.h"

class Client {
public:
    Client();
    ~Client();

public:
    void selectTraderType();
    void connectToServer();
    void displayMenu();
    void disconnectFromServer();
    void sendMessage(const std::string&);
    void clientCreateOrder();

private:
    const char* serverIP;
    int serverPort;
    int clientSocket;
    Trader* trader;
};

#endif  //CLIENT_H
