#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "archivedOrder.h"
#include "limitArchivedOrder.h"
#include "marketArchivedOrder.h"
#include "..\src\stock.h"
#include "..\src\trader.h"

#include <map>
#include <mutex>
#include <unordered_map>
#include <vector>

class OrderBook {
public:
    OrderBook();
    ~OrderBook();

public:
    void addOrder(ArchivedOrder*);
    void addStock(Stock*);
    void removeOrder(ArchivedOrder*);
    Stock* getStock(int) const;
    Trader* getTrader(int) const;

private:
    std::unordered_map<int, Stock*> stocks;
    std::unordered_map<int, Trader*> traders;
    std::unordered_map<int, std::vector<ArchivedOrder*>> orders;
    mutable std::mutex mtx; 
};

#endif // ORDER_BOOK_H
