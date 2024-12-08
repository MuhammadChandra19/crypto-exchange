#include "Limit.hpp"
#include <algorithm>

Limit::Limit(double price) : Price(price), TotalVolume(0.0) {}

void Limit::AddOrder(const std::shared_ptr<Order>& order) {
    OrderList.push_back(order);
    TotalVolume += order->Size;
    order->LimitPtr = std::make_shared<Limit>(*this);
}

void Limit::DeleteOrder(const std::shared_ptr<Order>& order) {
    auto it = std::find(OrderList.begin(), OrderList.end(), order);
    if (it != OrderList.end()) {
        TotalVolume -= order->Size;
        OrderList.erase(it);
        order->LimitPtr = nullptr;
    }
}

std::vector<Match> Limit::Fill(const std::shared_ptr<Order>& order) {
    std::vector<Match> matches;
    double remainingSize = order->Size;

    for (auto it = OrderList.begin(); it != OrderList.end() && remainingSize > 0;) {
        auto& currentOrder = *it;

        // Fill the orders
        Match match = fillOrder(order, currentOrder);
        matches.push_back(match);

        // Adjust the remaining size
        remainingSize -= match.SizeFilled;

        // Remove the filled order
        if (currentOrder->Size <= 0) {
            TotalVolume -= currentOrder->Size;
            it = OrderList.erase(it);
        } else {
            ++it;
        }
    }

    // Update the order's size
    order->Size = remainingSize;

    return matches;
}

Match Limit::fillOrder(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) {
    double sizeFilled = std::min(a->Size, b->Size);
    double fillPrice = Price;

    // Adjust order sizes
    a->Size -= sizeFilled;
    b->Size -= sizeFilled;

    // Return the match
    return Match{
        a->Bid ? nullptr : a,
        a->Bid ? a : nullptr,
        sizeFilled,
        fillPrice
    };
}
