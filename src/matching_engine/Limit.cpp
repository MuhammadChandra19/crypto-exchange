#include "Limit.hpp"
#include <algorithm>

Limit::Limit(double price) : Price(price), TotalVolume(0.0) {}

void Limit::AddOrder(const std::shared_ptr<Order>& order) {
    OrderList.push_back(order);
    TotalVolume += order->Size;
    // Ensure the order's LimitPtr points back to this Limit instance
    order->LimitPtr = shared_from_this();
}

void Limit::DeleteOrder(const std::shared_ptr<Order>& order) {
    auto it = std::find(OrderList.begin(), OrderList.end(), order);
    if (it != OrderList.end()) {
        // Replace the found order with the last order
        *it = OrderList.back();
        OrderList.pop_back();  // Remove the last order
    }

    // Set the limit reference of the order to nullptr
    order->LimitPtr = nullptr;
    TotalVolume -= order->Size;

    std::sort(OrderList.begin(), OrderList.end(), [](Order* lhs, Order* rhs) {
        return lhs->Timestamp < rhs->Timestamp;
    });

}

std::vector<Match> Limit::Fill(const std::shared_ptr<Order>& order) {
    std::vector<Match> matches;
    std::vector<std::shared_ptr<Order>> ordersToDelete;

    double remainingSize = order->Size;

    for (auto it = OrderList.begin(); it != OrderList.end() && remainingSize > 0;) {
        auto& currentOrder = *it;
        Match match = fillOrder(currentOrder, order);

        // Record the match
        matches.push_back(match);
        TotalVolume -= match.SizeFilled;

        if (currentOrder->IsFilled()) {
            ordersToDelete.push_back(currentOrder);
        }

        if (order->IsFilled()) {
            break;
        }
    }

    for (auto it = ordersToDelete.begin(); it != ordersToDelete.end();) {
        DeleteOrder(*it);
    }


    return matches;
}

Match Limit::fillOrder(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) {
    std::shared_ptr<Order> bid;
    std::shared_ptr<Order> ask;
    double sizeFilled = 0.0;

    // Determine bid and ask orders
    if (a->Bid) {
        bid = a;
        ask = b;
    } else {
        bid = b;
        ask = a;
    }

    // Adjust sizes and determine the size filled
    if (a->Size > b->Size) {
        a->Size -= b->Size;
        sizeFilled = b->Size;
        b->Size = 0.0;
    } else {
        b->Size -= a->Size;
        sizeFilled = a->Size;
        a->Size = 0.0;
    }

    // Return the match result
    return Match{
        bid,           // Bid order
        ask,           // Ask order
        sizeFilled,    // Size filled
        Price          // Price of the limit
    };
}
