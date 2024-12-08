#include "OrderBook.hpp"
#include <algorithm>
#include <numeric>

OrderBook::OrderBook() = default;

// Calculate total volume of asks
double OrderBook::AskTotalVolume() const {
    return std::accumulate(Asks.begin(), Asks.end(), 0.0,
        [](const double sum, const std::shared_ptr<Limit>& limit) {
            return sum + limit->TotalVolume;
        });
}

// Calculate total volume of bids
double OrderBook::BidTotalVolume() const {
    return std::accumulate(Bids.begin(), Bids.end(), 0.0,
        [](const double sum, const std::shared_ptr<Limit>& limit) {
            return sum + limit->TotalVolume;
        });
}

// Cancel an existing order
void OrderBook::CancelOrder(const std::shared_ptr<Order>& order) {
    const auto match_order = Orders.find(order->ID);
    if (match_order == Orders.end()) {
        return; // Order not found
    }

    if (const auto limit = order->LimitPtr) {
        limit->DeleteOrder(order);

        // Remove empty limits
        if (limit->OrderList.empty()) {
            clearLimit(order->Bid, limit);
        }
    }

    Orders.erase(match_order);
}

// Place a limit order
void OrderBook::PlaceLimitOrder(const double price, const std::shared_ptr<Order>& order) {
    const auto limit = FindOrCreateLimit(price, order->Bid);
    order->LimitPtr = limit;
    limit->AddOrder(order);
    Orders[order->ID] = order;
}

// Place a market order and match it with existing orders
std::vector<Match> OrderBook::PlaceMarketOrder(const std::shared_ptr<Order>& order) {
    std::vector<Match> matches;
    const auto & limits = order->Bid ? Asks : Bids; // Select the opposite side of the orderbook

    double remainingSize = order->Size;

    while (!limits.empty() && remainingSize > 0) {
        const auto& bestLimit = limits.front();

        while (!bestLimit->OrderList.empty() && remainingSize > 0) {
            auto bestOrder = bestLimit->OrderList.front();

            double const sizeFilled = std::min(remainingSize, bestOrder->Size);
            double const fillPrice = bestLimit->Price;

            // Record the match
            matches.emplace_back(
                bestOrder->Bid ? nullptr : bestOrder, // Counterparty's ask order
                bestOrder->Bid ? bestOrder : nullptr, // Counterparty's bid order
                sizeFilled,
                fillPrice
            );

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
void OrderBook::clearLimit(const bool bid, const std::shared_ptr<Limit>& limit) {
    auto& limitMap = bid ? BidLimits : AskLimits;
    auto& limitsList = bid ? Bids : Asks;

    limitMap.erase(limit->Price);
    std::erase_if(limitsList, [&limit](const auto &l) { return l->Price == limit->Price; });
}

// Find or create a new limit for a given price
std::shared_ptr<Limit> OrderBook::FindOrCreateLimit(double price, bool isBid) {
    auto& limits = isBid ? Bids : Asks;
    auto& limitMap = isBid ? BidLimits : AskLimits;

    if (const auto match_limit = limitMap.find(price); match_limit != limitMap.end()) {
        return match_limit->second;
    }

    auto newLimit = std::make_shared<Limit>(price);
    limits.push_back(newLimit);
    limitMap[price] = newLimit;
    return newLimit;
}

// Remove an empty limit if it exists
void OrderBook::removeEmptyLimit(double price, bool isBid) {
    auto& limitMap = isBid ? BidLimits : AskLimits;

    if (const auto match_limit = limitMap.find(price);
        match_limit != limitMap.end() && match_limit->second->OrderList.empty()) {
        limitMap.erase(match_limit);
    }
}
