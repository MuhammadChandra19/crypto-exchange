#include "MatchingEngine.hpp"

#include <iostream>

#include "Order.hpp"

MatchingEngine::MatchingEngine() {
    std::cout << "MatchingEngine Initialized." << '\n';
}

MatchingEngine::~MatchingEngine() {
    std::cout << "MatchingEngine Destroyed." << '\n';
}

void MatchingEngine::initialize() {
    std::cout << "MatchingEngine is now ready." << '\n';
}

int64_t MatchingEngine::handlePlaceOrder(const PlaceOrderRequest &placeOrderRequest) {
    const auto limit = orderbook.FindOrCreateLimit(placeOrderRequest.price, placeOrderRequest.bid);
    auto const order = std::make_shared<Order>(
        placeOrderRequest.id,
        placeOrderRequest.userId,
        placeOrderRequest.size,
        placeOrderRequest.bid,
        limit,
        std::chrono::duration_cast<std::chrono::milliseconds>(
                                    std::chrono::system_clock::now().time_since_epoch())
                                    .count()
        );
    if (placeOrderRequest.orderType == 0) { // limit orders
        orderbook.PlaceLimitOrder(placeOrderRequest.price,order);
        return placeOrderRequest.id;
    }

    if (placeOrderRequest.orderType == 1) {
        orderbook.PlaceMarketOrder(order);
        return placeOrderRequest.id;
    }

    return 0;
}


