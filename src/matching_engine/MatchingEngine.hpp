#pragma once

#include <string>
#include <vector>

#include "OrderBook.hpp"

struct LiveOrder
{
    int64_t id;
    int64_t userId;
    double size;
    bool bid;
    int64_t timestamp;
};

struct PlaceOrderRequest {
    int64_t id;
    int64_t userId;
    int orderType;
    bool bid;
    double size;
    double price;
    std::string pair;
};

struct  OrderBookData
{
    double totalBidVolume;
    double totalAskVolume;
    std::vector<std::shared_ptr<LiveOrder>> asks;
    std::vector<std::shared_ptr<LiveOrder>> bids;
};



class MatchingEngine {
public:
    OrderBook orderbook;
    MatchingEngine();
    ~MatchingEngine();

    static void initialize();

    int64_t handlePlaceOrder(const PlaceOrderRequest& placeOrderRequest);
    OrderBookData getOrderBookData();
    void handleCancelOrder(std::string id);
};
