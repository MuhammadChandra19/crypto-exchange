#pragma once

#include <memory>
#include <vector>
#include "Order.hpp"
#include "Match.hpp"

class Limit : public std::enable_shared_from_this<Limit> {
public:
    double Price;
    double TotalVolume;
    std::vector<std::shared_ptr<Order>> OrderList;

    explicit Limit(double price);
    void AddOrder(const std::shared_ptr<Order>& order);
    void DeleteOrder(const std::shared_ptr<Order>& order);
    std::vector<Match> Fill(const std::shared_ptr<Order>& order);

private:
    Match fillOrder(const std::shared_ptr<Order>& a_order, const std::shared_ptr<Order>& b_order) const;
};

using Limits = std::vector<std::shared_ptr<Limit>>;
