#include "stock.h"

#include <fstream>

Stock::Stock(Stock&& other) {
    id = other.id;
    price = other.price;
    count = other.count;
}

int Stock::getID() const{
    return id;
}

int Stock::getCount() const{
    return count;
}

double Stock::getPrice() const{
    return price;
}

void Stock::setID(int newID) {
    id = newID;
}

void Stock::setPrice(double newPrice) {
    price = newPrice;
}

void Stock::setCount(int newCount) {
    count = newCount;
}

Stock Stock::loadStockFromID(int targetID) {
    std::ifstream file("../server/stocks.txt");
    if (!file.is_open()) {
        return Stock(-1, 0.0, 0); 
    }
    std::string line;
    while (std::getline(file, line)) {
        int id, count;
        double price;
        if (sscanf(line.c_str(), "Stock ID: %d, Price: %lf, Count: %d", &id, &price, &count) == 3) {
            if (id == targetID) {
                return Stock(id, price, count);
            }
        }
    }
    return Stock(-1, 0.0, 0); 
}
