#include "MarketDataPublisher.hpp"

MarketDataPublisher::MarketDataPublisher() {
    std::cout << "MarketDataPublisher Initialized." << std::endl;
}

MarketDataPublisher::~MarketDataPublisher() {
    std::cout << "MarketDataPublisher Destroyed." << std::endl;
}

void MarketDataPublisher::publishData() {
    std::cout << "Publishing market data..." << std::endl;
}
