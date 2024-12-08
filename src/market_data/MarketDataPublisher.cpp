#include "MarketDataPublisher.hpp"

MarketDataPublisher::MarketDataPublisher() {
    std::cout << "MarketDataPublisher Initialized." << '\n';
}

MarketDataPublisher::~MarketDataPublisher() {
    std::cout << "MarketDataPublisher Destroyed." << '\n';
}

void MarketDataPublisher::publishData() {
    std::cout << "Publishing market data..." << '\n';
}
