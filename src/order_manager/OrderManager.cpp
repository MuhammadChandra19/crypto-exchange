#include "OrderManager.hpp"

OrderManager::OrderManager() {
    std::cout << "OrderManager Initialized." << '\n';
}

OrderManager::~OrderManager() {
    std::cout << "OrderManager Destroyed." << '\n';
}

void OrderManager::processOrder(const std::string& order) {
    std::cout << "OrderManager received order: " << order << '\n';
}
