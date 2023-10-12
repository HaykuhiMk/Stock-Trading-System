#include "order.h"

#include <iostream>

Trader* Order::getTrader() const {
    return trader;
}

Stock* Order::getStock() const {
    return stock;
}

int Order::getCount() const {
    return count;
}

int Order::getID() const {
    return 0;
}

void Order::setTrader(Trader* newTrader) {
    trader = newTrader;
}

void Order::setStock(Stock* newStock) {
    stock = newStock;
}

void Order::setCount(int newCount) {
    count = newCount;
}

