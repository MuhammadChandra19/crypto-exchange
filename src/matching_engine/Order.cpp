#include "Order.hpp"

Order::Order(int64_t id, int64_t user_id, double size, bool bid, std::shared_ptr<Limit> limit, int64_t timestamp)
    : ID(id), UserID(user_id), Size(size), Bid(bid), LimitPtr(std::move(limit)), Timestamp(timestamp) {}
