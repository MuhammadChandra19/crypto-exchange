#pragma once

#include <memory>
#include <vector>
#include <cstdint>

class Limit;

class Order {
public:
    int64_t ID;
    int64_t UserID;
    double Size;
    bool Bid;
    std::shared_ptr<Limit> LimitPtr;
    int64_t Timestamp;

    Order(int64_t id, int64_t user_id, double size, bool bid, std::shared_ptr<Limit> limit, int64_t timestamp);
};

using Orders = std::vector<std::shared_ptr<Order>>;
