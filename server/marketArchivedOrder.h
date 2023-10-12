#ifndef MARKET_ARCHIVED_ORDER_H
#define MARKET_ARCHIVED_ORDER_H

#include "archivedOrder.h"

class MarketArchivedOrder : public ArchivedOrder {
public:
    MarketArchivedOrder(int id, int traderID, int stockID, int count) :
        ArchivedOrder(id, traderID, stockID, count) {}
};

#endif  // MARKET_ARCHIVED_ORDER_H
