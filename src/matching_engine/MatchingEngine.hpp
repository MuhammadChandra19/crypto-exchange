#pragma once

#include <string>
#include <iostream>

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();

    static void initialize();
    static void processOrder(const std::string& order);
};
