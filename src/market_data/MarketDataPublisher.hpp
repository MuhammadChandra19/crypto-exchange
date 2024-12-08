#pragma once


#include <iostream>
#include <string>

class MarketDataPublisher {
public:
    MarketDataPublisher();
    ~MarketDataPublisher();

    static void publishData();
};
