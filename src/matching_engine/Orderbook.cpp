#include "Orderbook.hpp"
#include <algorithm>
#include <numeric>

Orderbook::Orderbook() = default;

// Calculate total volume of asks
double Orderbook::AskTotalVolume() const {
    return std::accumulate(Asks.begin(), Asks.end(), 0.0,
        [](double sum, const std::shared_ptr<Limit>& limit) {
            return sum + limit->TotalVolume;
        });
}

// Calculate total volume of bids
double Orderbook::BidTotalVolume() const {
    return std::accumulate(Bids.begin(), Bids.end(), 0.0,
        [](double sum, const std::shared_ptr<Limit>& limit) {
            return sum + limit->TotalVolume;
        });
}

// Cancel an existing order
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

// Place a limit order
void Orderbook::PlaceLimitOrder(double price, const std::shared_ptr<Order>& order) {
    auto limit = FindOrCreateLimit(price, order->Bid);
    order->LimitPtr = limit;
    limit->AddOrder(order);
    Orders[order->ID] = order;
}

// Place a market order and match it with existing orders
std::vector<Match> Orderbook::PlaceMarketOrder(const std::shared_ptr<Order>& order) {
    std::vector<Match> matches;
    auto& limits = order->Bid ? Asks : Bids; // Select the opposite side of the orderbook

    double remainingSize = order->Size;

    while (!limits.empty() && remainingSize > 0) {
        auto& bestLimit = limits.front();

        while (!bestLimit->OrderList.empty() && remainingSize > 0) {
            auto bestOrder = bestLimit->OrderList.front();

            double sizeFilled = std::min(remainingSize, bestOrder->Size);
            double fillPrice = bestLimit->Price;

            // Record the match
            matches.push_back(Match{
                bestOrder->Bid ? nullptr : bestOrder, // Counterparty's ask order
                bestOrder->Bid ? bestOrder : nullptr, // Counterparty's bid order
                sizeFilled,
                fillPrice
            });

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

// Clear an empty limit from the orderbook
void Orderbook::clearLimit(bool bid, const std::shared_ptr<Limit>& limit) {
    auto& limitMap = bid ? BidLimits : AskLimits;
    auto& limitsList = bid ? Bids : Asks;

    limitMap.erase(limit->Price);
    limitsList.erase(std::remove_if(limitsList.begin(), limitsList.end(),
        [&limit](const auto& l) { return l->Price == limit->Price; }),
        limitsList.end());
}

// Find or create a new limit for a given price
std::shared_ptr<Limit> Orderbook::FindOrCreateLimit(double price, bool isBid) {
    auto& limits = isBid ? Bids : Asks;
    auto& limitMap = isBid ? BidLimits : AskLimits;

    auto it = limitMap.find(price);
    if (it != limitMap.end()) {
        return it->second;
    }

    auto newLimit = std::make_shared<Limit>(price);
    limits.push_back(newLimit);
    limitMap[price] = newLimit;
    return newLimit;
}

// Remove an empty limit if it exists
void Orderbook::removeEmptyLimit(double price, bool isBid) {
    auto& limitMap = isBid ? BidLimits : AskLimits;
    auto it = limitMap.find(price);

    if (it != limitMap.end() && it->second->OrderList.empty()) {
        limitMap.erase(it);
    }
}
