#ifndef MATCHING_ENGINE_HPP
#define MATCHING_ENGINE_HPP

#include <string>
#include <iostream>

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();

    void initialize();
    void processOrder(const std::string& order);
};

#endif // MATCHING_ENGINE_HPP
