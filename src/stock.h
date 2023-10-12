#ifndef STOCK_H
#define STOCK_H

#include "order.h"

#include <mutex>

class Stock {
public:
    Stock() = default;
    Stock(int id, double price, int count) : 
        id(id), price(price), count(count) 
        {}
    Stock(Stock&&);

public:
    int getID() const;
    double getPrice() const;
    int getCount() const;
    void setID(int);
    void setPrice(double);
    void setCount(int);
    Stock loadStockFromID(int);

private:
    int id;
    double price;
    int count;
    mutable std::mutex mtx;
};

#endif  //STOCK_H
