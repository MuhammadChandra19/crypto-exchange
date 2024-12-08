#include "Orderbook.hpp"
#include <algorithm>
#include <numeric>

Orderbook::Orderbook() = default;

double Orderbook::AskTotalVolume() const {
    return std::accumulate(Asks.begin(), Asks.end(), 0.0, [](double sum, const std::shared_ptr<Limit>& limit) {
        return sum + limit->TotalVolume;
    });
}

double Orderbook::BidTotalVolume() const {
    return std::accumulate(Bids.begin(), Bids.end(), 0.0, [](double sum, const std::shared_ptr<Limit>& limit) {
        return sum + limit->TotalVolume;
    });
}

void Orderbook::CancelOrder(const std::shared_ptr<Order>& order) {
    auto it = Orders.find(order->ID);
    if (it == Orders.end()) {
        return; // Order not found
    }

    auto limit = order->LimitPtr;
    if (limit) {
        limit->DeleteOrder(order);

        // Remove empty limits
        if (limit->OrderList.empty()) {
            clearLimit(order->Bid, limit);
        }
    }

    Orders.erase(it);
}

void Orderbook::PlaceLimitOrder(double price, const std::shared_ptr<Order>& order) {
    auto limit = FindOrCreateLimit(price, order->Bid);
    order->LimitPtr = limit;
    limit->AddOrder(order);
    Orders[order->ID] = order;
}

std::vector<Match> Orderbook::PlaceMarketOrder(const std::shared_ptr<Order>& order) {
    std::vector<Match> matches;
    auto& limits = order->Bid ? Asks : Bids;

    double remainingSize = order->Size;

    while (!limits.empty() && remainingSize > 0) {
        auto& bestLimit = limits.front();

        while (!bestLimit->OrderList.empty() && remainingSize > 0) {
            auto bestOrder = bestLimit->OrderList.front();

            double sizeFilled = std::min(remainingSize, bestOrder->Size);
            double fillPrice = bestLimit->Price;

            // Record the match
            matches.push_back(Match{bestOrder->Bid ? nullptr : bestOrder, bestOrder->Bid ? bestOrder : nullptr, sizeFilled, fillPrice});

            // Adjust order sizes
            remainingSize -= sizeFilled;
            bestOrder->Size -= sizeFilled;

            if (bestOrder->Size == 0) {
                bestLimit->DeleteOrder(bestOrder);
                Orders.erase(bestOrder->ID);
            }
        }

        // Remove empty limit
        if (bestLimit->OrderList.empty()) {
            clearLimit(order->Bid, bestLimit);
        }
    }

    return matches;
}

void Orderbook::clearLimit(bool bid, const std::shared_ptr<Limit>& limit) {
    auto& limitMap = bid ? BidLimits : AskLimits;
    auto& limitsList = bid ? Bids : Asks;

    limitMap.erase(limit->Price);
    limitsList.erase(std::remove_if(limitsList.begin(), limitsList.end(),
        [&limit](const auto& l) { return l->Price == limit->Price; }),
        limitsList.end());
}

std::shared_ptr<Limit> Orderbook::FindOrCreateLimit(double price, bool isBid) {
    auto& limits = isBid ? BidLimits : AskLimits;
    auto it = limits.find(price);

    if (it != limits.end()) {
        // Return the existing limit
        return it->second;
    }

    // Create a new limit
    auto newLimit = std::make_shared<Limit>(price);
    limits[price] = newLimit;
    return newLimit;
}

void Orderbook::removeEmptyLimit(double price, bool isBid) {
    auto& limits = isBid ? BidLimits : AskLimits;
    auto it = limits.find(price);

    if (it != limits.end() && it->second->OrderList.empty()) {
        // Remove the limit if no orders exist
        limits.erase(it);
    }
}
