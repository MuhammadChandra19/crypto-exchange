#pragma once

#include <string>
#include <iostream>

class OrderManager {
public:
    OrderManager();
    ~OrderManager();

    void processOrder(const std::string& order);
};
