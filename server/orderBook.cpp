#include "orderBook.h"

#include <iostream>
#include <algorithm>

OrderBook::OrderBook() {}

OrderBook::~OrderBook() {
    for (auto& pair : stocks) {
        delete pair.second;
    }
    for (auto& pair : orders) {
        for (ArchivedOrder* order : pair.second) {
            delete order;
        }
    }
}

void OrderBook::addOrder(ArchivedOrder* newOrder) {
    std::lock_guard<std::mutex> lock(mtx); // Lock to ensure thread safety
    int stockID = newOrder->getStockID();
    orders[stockID].push_back(newOrder);
}

void OrderBook::addStock(Stock* newStock) {
    int stockID = newStock->getID();
    auto result = stocks.emplace(stockID, newStock);
    if (!result.second) {
        std::cerr << "Error: Stock with ID " << stockID << " already exists." << std::endl;
    }
}

void OrderBook::removeOrder(ArchivedOrder* order) {
    int stockID = order->getStockID();
    auto it = orders.find(stockID);
    if (it != orders.end()) {
        std::vector<ArchivedOrder*>& stockOrders = it->second;
        stockOrders.erase(std::remove_if(stockOrders.begin(), stockOrders.end(),    //from algorithm
            [order](ArchivedOrder* ord) { return ord == order; }), stockOrders.end());
        delete order;
        if (stockOrders.empty()) {
            orders.erase(it);
        }
    }
}

Stock* OrderBook::getStock(int stockID) const {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = stocks.find(stockID);
    return (it != stocks.end()) ? it->second : nullptr;
}

Trader* OrderBook::getTrader(int traderID) const {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = traders.find(traderID);
    return (it != traders.end()) ? it->second : nullptr;
}
