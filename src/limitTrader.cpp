#include "limitTrader.h"
#include "limitOrder.h"

#include <iostream>

std::string LimitTrader::createOrder(Stock* stock) {
    int orderID;
    int count;
    double price;
    std::cout << "Enter Order ID: ";
    std::cin >> orderID;
    std::cout << "Enter Order Quantity: ";
    std::cin >> count;
    std::cout << "Enter Price: ";
    std::cin >> price;
    Order* limitOrder = new LimitOrder(orderID, this, stock, count, price);
    std::cout << "COUNT INTO  createOrder" << count << std::endl;
    this->addOrder(limitOrder);
    limitOrder->execute();
    return limitOrder->serializeToString();
}
