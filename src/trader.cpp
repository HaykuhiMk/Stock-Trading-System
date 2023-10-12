#include "trader.h"

#include <iostream>

int Trader::getID() const {
    return id;
}

char Trader::getType() const {
    return type;
}

double Trader::getBalance() const {
    return balance;
}

const std::vector<Stock*>& Trader::getStocks() const {
    return stocks;
}

const std::vector<Order*>& Trader::getOrders() const {
    return orders;
}

void Trader::setId(int newId) {
    id = newId;
}

void Trader::setType(char newType) {
    type = newType;
}

void Trader::setBalance(double newBalance) {
    balance = newBalance;
}

void Trader::addStock(Stock* stock) {
    stocks.push_back(stock);
}

void Trader::addOrder(Order* order) {
    orders.push_back(order);
}

Stock* Trader::findStock(int stockID) const {
    for (Stock* stock : stocks) {
        if (stock->getID() == stockID) {
            return stock;
        }
    }
    return nullptr;
}
