#pragma once

#include "Limit.hpp"
#include "Match.hpp"
#include <map>
#include <unordered_map>
#include <memory>
#include <vector>

class Orderbook {
public:
    // Containers for ask and bid limits
    Limits Asks;
    Limits Bids;

    // Maps for fast lookup
    std::map<double, std::shared_ptr<Limit>> AskLimits;
    std::map<double, std::shared_ptr<Limit>> BidLimits;
    std::unordered_map<int64_t, std::shared_ptr<Order>> Orders;

    Orderbook();

    // Core methods
    double AskTotalVolume() const;
    double BidTotalVolume() const;
    void CancelOrder(const std::shared_ptr<Order>& order);
    void PlaceLimitOrder(double price, const std::shared_ptr<Order>& order);
    std::vector<Match> PlaceMarketOrder(const std::shared_ptr<Order>& order);
    std::shared_ptr<Limit> FindOrCreateLimit(double price, bool isBid);


    // Getters for sorted limits
    const Limits& GetAsks() const {
        Limits sortedAsks = Asks;

        std::sort(sortedAsks.begin(), sortedAsks.end(), [](const Limit& a, const Limit& b) {
            return a.Price < b.Price;
        });

        return sortedAsks;
    }
    const Limits& GetBids() const {
        Limits sortedBids = Bids;

        std::sort(sortedBids.begin(), sortedBids.end(), [](const Limit& a, const Limit& b) {
            return a.Price > b.Price;
        });

        return sortedBids;
    }

private:

    void removeEmptyLimit(double price, bool isBid);
    void clearLimit(bool bid, const std::shared_ptr<Limit>& limit);
};
