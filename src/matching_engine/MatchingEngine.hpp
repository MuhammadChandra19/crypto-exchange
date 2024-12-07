#pragma once

#include <string>
#include <iostream>

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();

    void initialize();
    void processOrder(const std::string& order);
};
