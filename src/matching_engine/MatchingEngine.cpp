#include "MatchingEngine.hpp"

MatchingEngine::MatchingEngine() {
    std::cout << "MatchingEngine Initialized." << '\n';
}

MatchingEngine::~MatchingEngine() {
    std::cout << "MatchingEngine Destroyed." << '\n';
}

void MatchingEngine::initialize() {
    std::cout << "MatchingEngine is now ready." << '\n';
}

void MatchingEngine::processOrder(const std::string& order) {
    std::cout << "Processing order: " << order << '\n';
}
