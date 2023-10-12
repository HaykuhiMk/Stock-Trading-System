#include "client.h"

#include <iostream>

int main() {
    Client client;
    client.connectToServer();
    client.selectTraderType();
    client.displayMenu();
    return 0;
}
