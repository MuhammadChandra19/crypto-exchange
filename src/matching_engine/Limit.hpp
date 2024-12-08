#pragma once

#include "Order.hpp"
#include "Match.hpp"
#include <vector>
#include <memory>

class Limit {
public:
    double Price;
    Orders OrderList;
    double TotalVolume;

    Limit(double price);

    void AddOrder(const std::shared_ptr<Order>& order);
    void DeleteOrder(const std::shared_ptr<Order>& order);
    std::vector<Match> Fill(const std::shared_ptr<Order>& order);

private:
    Match fillOrder(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b);
};

using Limits = std::vector<std::shared_ptr<Limit>>;
