#include "archivedOrder.h"

int ArchivedOrder::getTraderID() const {
    return traderID;
}

int ArchivedOrder::getStockID() const {
    return stockID;
}

int ArchivedOrder::getCount() const {
    return count;
}

int ArchivedOrder::getID() const {
    return id;
}

void ArchivedOrder::setTraderID(int newTraderID) {
    traderID = newTraderID;
}

void ArchivedOrder::setStockID(int newStockID) {
    stockID = newStockID;
}

void ArchivedOrder::setCount(int newCount) {
    count = newCount;
}
