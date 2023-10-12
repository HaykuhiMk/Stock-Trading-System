#ifndef ORDER_H
#define ORDER_H

#include <string>

class Trader;
class Stock;

class Order {
public:
    Order(int id, Trader* trader, Stock* stock, int count) : 
        id(id), trader(trader), stock(stock), count(count) 
        {}
    virtual ~Order() = default;

public:
    Trader* getTrader() const;
    Stock* getStock() const;
    int getCount() const;
    int getID() const;
    void setTrader(Trader*);
    void setStock(Stock*);
    void setCount(int);
    virtual void execute() = 0;
    virtual std::string serializeToString() const = 0;

private:
    int id;
    Trader* trader;
    Stock* stock;
    int count;
};

#endif  //ORDER_H