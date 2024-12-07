#include "Match.hpp"

Match::Match(std::shared_ptr<Order> ask, std::shared_ptr<Order> bid, double size_filled, double price)
    : Ask(std::move(ask)), Bid(std::move(bid)), SizeFilled(size_filled), Price(price) {}
