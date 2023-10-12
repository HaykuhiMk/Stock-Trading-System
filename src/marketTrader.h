#ifndef MARKET_TRADER_H
#define MARKET_TRADER_H

#include "trader.h"

class MarketTrader : public Trader {
public:
    MarketTrader(int id, double balance) : Trader(id, balance) {}
    ~MarketTrader() = default;

public:
    std::string createOrder(Stock*) override;
};

#endif  //MARKET_TRADER_H