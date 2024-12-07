#include "MatchingEngine.hpp"

MatchingEngine::MatchingEngine() {
    std::cout << "MatchingEngine Initialized." << std::endl;
}

MatchingEngine::~MatchingEngine() {
    std::cout << "MatchingEngine Destroyed." << std::endl;
}

void MatchingEngine::initialize() {
    std::cout << "MatchingEngine is now ready." << std::endl;
}

void MatchingEngine::processOrder(const std::string& order) {
    std::cout << "Processing order: " << order << std::endl;
}
