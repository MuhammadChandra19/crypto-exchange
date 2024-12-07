#include "OrderManager.hpp"

OrderManager::OrderManager() {
    std::cout << "OrderManager Initialized." << std::endl;
}

OrderManager::~OrderManager() {
    std::cout << "OrderManager Destroyed." << std::endl;
}

void OrderManager::processOrder(const std::string& order) {
    std::cout << "OrderManager received order: " << order << std::endl;
}
