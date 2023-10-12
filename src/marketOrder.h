#ifndef MARKET_ORDER_H
#define MARKET_ORDER_H

#include "order.h"

class MarketOrder : public Order {
public:
    MarketOrder(int id, Trader* trader, Stock* stock, int count) :
        Order(id, trader, stock, count) {}
    ~MarketOrder() = default;

public:
    void execute() override;
    std::string serializeToString() const override;
};

#endif  //MARKET_ORDER_H