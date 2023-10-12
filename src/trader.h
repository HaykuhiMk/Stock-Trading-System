#ifndef TRADER_H
#define TRADER_H

#include "stock.h"
#include "order.h"

#include <vector>
#include <string>

class Trader {
public:
    Trader(int id, double balance) : id(id), balance(balance) {}
    virtual ~Trader() = default;

public:
    int getID() const;
    char getType() const;
    double getBalance() const;
    const std::vector<Stock*>& getStocks() const;
    const std::vector<Order*>& getOrders() const;
    void setId(int);
    void setType(char);
    void setBalance(double);
    void addOrder(Order*);
    void addStock(Stock*);
    Stock* findStock(int) const;
    virtual std::string createOrder(Stock*) = 0;

private:
    int id;
    double balance;
    char type;
    std::vector<Stock*> stocks;
    std::vector<Order*> orders;
};

#endif  //TRADER_H
