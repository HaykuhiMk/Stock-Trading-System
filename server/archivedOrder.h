#ifndef ARCHIVED_ORDER_H
#define ARCHIVED_ORDER_H

class ArchivedOrder {
public:
    ArchivedOrder(int id, int traderID, int stockID, int count) : 
        id(id), traderID(traderID), stockID(stockID), count(count) 
        {}
    ~ArchivedOrder() = default;

public:
    int getTraderID() const;
    int getStockID() const;
    int getCount() const;
    int getID() const;
    void setTraderID(int);
    void setStockID(int);
    void setCount(int);

private:
    int id;
    int traderID;
    int stockID;
    int count;
};

#endif  //ARCHIVED_ORDER_H