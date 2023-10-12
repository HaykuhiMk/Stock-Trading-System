#ifndef LIMIT_TRADER_H
#define LIMIT_TRADER_H

#include "trader.h"

class LimitTrader : public Trader {
public:
    LimitTrader(int id, double balance) : Trader(id, balance) {}
    ~LimitTrader() = default;

public:
    std::string createOrder(Stock*) override;
};

#endif  //LIMIT_TRADER_H