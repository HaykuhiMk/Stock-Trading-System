#ifndef LIMIT_ARCHIVED_ORDER_H
#define LIMIT_ARCHIVED_ORDER_H

#include "archivedOrder.h"

class LimitArchivedOrder : public ArchivedOrder {
public:
    LimitArchivedOrder(int id, int traderID, int stockID, int count, double price) :
        ArchivedOrder(id, traderID, stockID, count), price(price) {}

public:
    double getPrice() const;
    void setPrice(double newPrice);

private:
    double price;
};

#endif  // LIMIT_ARCHIVED_ORDER_H
