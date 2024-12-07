#ifndef ORDER_MANAGER_HPP
#define ORDER_MANAGER_HPP

#include <string>
#include <iostream>

class OrderManager {
public:
    OrderManager();
    ~OrderManager();

    void processOrder(const std::string& order);
};

#endif // ORDER_MANAGER_HPP
