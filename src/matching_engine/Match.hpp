#pragma once
#include "Order.hpp"

class Match {
public:
    std::shared_ptr<Order> Ask;
    std::shared_ptr<Order> Bid;
    double SizeFilled;
    double Price;

    Match(std::shared_ptr<Order> ask, std::shared_ptr<Order> bid, double size_filled, double price);
};
