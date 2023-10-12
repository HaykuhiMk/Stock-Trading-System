#include "limitOrder.h"
#include "trader.h"

#include <iostream>

void LimitOrder::setPrice(double newPrice) {
    price = newPrice;
}

double LimitOrder::getPrice() const {
    return price;
}

void LimitOrder::execute() {
    int orderCount = this->getCount();
    double orderPrice = this->getPrice();
    Stock* stock =  this->getStock();
    Trader* trader = this->getTrader();
    double limitPrice = stock->getPrice();
    // Check if the order is a buy or sell order
    if (orderCount > 0) {
        // It's a buy limit order
        std::cout << "Execution of a buy Limit Order for " << orderCount << " shares" << std::endl;
        if (trader->getBalance() >= limitPrice * orderCount && stock->getCount() >= orderCount && orderPrice >= limitPrice) {
            trader->setBalance(trader->getBalance() - limitPrice * orderCount);
            trader->addStock(stock);
            stock->setCount(stock->getCount() - orderCount);
            std::cout << "The Buy Limit Order executed successfully!" << std::endl;
        } else {
            std::cout << "Buy Limit Order execution failed due to insufficient funds or price conditions." << std::endl;        
        }
    } else if (orderCount < 0) {
        // It's a sell limit order
        Stock* traderStock = trader->findStock(stock->getID());
        std::cout << "Execution of a sell Limit Order for " << -orderCount << " shares" << std::endl;
        if (traderStock && traderStock->getCount() >= orderCount && orderPrice <= limitPrice) {
            trader->setBalance(trader->getBalance() + limitPrice * -orderCount);
            traderStock->setCount(stock->getCount() - -orderCount);
            std::cout << "The Sell Limit Order executed successfully!" << std::endl;
        } else {
            std::cout << "Sell Limit Order execution failed due to insufficient funds or price conditions." << std::endl;   
        }
    }
}

std::string LimitOrder::serializeToString() const {
    //CSV string
    std::string serializedData = std::to_string(this->getID()) + "," + std::to_string(getTrader()->getID()) + ","
        + std::to_string(getStock()->getID()) + "," + std::to_string(this->getCount()) + "," + std::to_string(this->getPrice()) + ",LimitOrder";
    return serializedData;
}