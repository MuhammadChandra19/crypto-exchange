#pragma once

#include <string>
#include <iostream>

class OrderManager {
public:
    OrderManager();
    ~OrderManager();

    static void processOrder(const std::string& order);
};
