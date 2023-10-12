#include "marketOrder.h"
#include "trader.h"

#include <iostream>

void MarketOrder::execute() {
    int orderCount = this->getCount();
    Stock* stock =  this->getStock();
    Trader* trader = this->getTrader();
    double marketPrice = stock->getPrice();
    // Check if the order is a buy or sell order
    if (orderCount > 0) {
        // It's a buy market order
        std::cout << "Execution of a buy Market Order for " << orderCount << " shares" << std::endl;
        if (trader->getBalance() >= marketPrice * orderCount && stock->getCount() >= orderCount) {
            trader->setBalance(trader->getBalance() - marketPrice * orderCount);
            trader->addStock(stock);
            stock->setCount(stock->getCount() - orderCount);
            std::cout << "The Buy Market Order executed successfully!" << std::endl;
        } else {
            std::cout << "Buy Market Order execution failed due to insufficient funds or stock count." << std::endl;
        }
    } else if (orderCount < 0) {
        // It's a sell market order
        std::cout << "Execution of a sell Market Order for " << -orderCount << " shares" << std::endl;
        Stock* traderStock = trader->findStock(stock->getID());
        if (traderStock && traderStock->getCount() >= orderCount) {
            trader->setBalance(trader->getBalance() + marketPrice * -orderCount);
            traderStock->setCount(stock->getCount() - -orderCount);
            std::cout << "The Sell Market Order executed successfully!" << std::endl;
        } else {
            std::cout << "Sell Market Order execution failed due to insufficient stock count." << std::endl;
        }
    }
}

std::string MarketOrder::serializeToString() const {
    //CSV string
    std::string serializedData = std::to_string(this->getID()) + "," + std::to_string(getTrader()->getID()) + ","
        + std::to_string(getStock()->getID()) + "," + std::to_string(this->getCount()) + ",MarketOrder";
    return serializedData;
}
