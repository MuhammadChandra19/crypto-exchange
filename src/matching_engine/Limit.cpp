#include "Limit.hpp"

Limit::Limit(double price) : Price(price), TotalVolume(0.0) {}

void Limit::addOrder(const std::shared_ptr<Order>& order) {
    OrderList.push_back(order);
    TotalVolume += order->Size;
}

void Limit::removeOrder(const std::shared_ptr<Order>& order) {
    auto it = std::find(OrderList.begin(), OrderList.end(), order);
    if (it != OrderList.end()) {
        TotalVolume -= (*it)->Size;
        OrderList.erase(it);
    }
}
