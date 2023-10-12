#include "marketTrader.h"
#include "marketOrder.h"

#include <iostream>

std::string MarketTrader::createOrder(Stock* stock) {
    int orderID;
    int count;
    std::cout << "Enter Order ID: ";
    std::cin >> orderID;
    std::cout << "Enter Order Quantity: ";
    std::cin >> count;
    Order* marketOrder = new MarketOrder(orderID, this, stock, count);
    this->addOrder(marketOrder);
    marketOrder->execute();
    return marketOrder->serializeToString();
}
