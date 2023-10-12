#ifndef LIMIT_ORDER_H
#define LIMIT_ORDER_H

#include "order.h"

class LimitOrder : public Order {
public:
     LimitOrder(int id, Trader* trader, Stock* stock, int count, double price) :
        Order(id, trader, stock, count), price(price) {}
    ~LimitOrder() = default;

public:
    void setPrice(double);
    double getPrice() const;
    void execute() override;
    std::string serializeToString() const override;

private:
    double price;
};

#endif  //LIMIT_ORDER_H