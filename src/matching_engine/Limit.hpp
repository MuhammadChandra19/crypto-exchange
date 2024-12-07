#pragma once
#include "Order.hpp"

class Limit {
public:
    double Price;
    Orders OrderList;
    double TotalVolume;

    Limit(double price);

    void addOrder(const std::shared_ptr<Order>& order);
    void removeOrder(const std::shared_ptr<Order>& order);
};

using Limits = std::vector<std::shared_ptr<Limit>>;
