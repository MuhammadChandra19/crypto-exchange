set(SOURCES
    MarketDataPublisher.cpp
)

set(HEADERS
    MarketDataPublisher.hpp
        main.cpp
)

add_library(market_data STATIC ${SOURCES} ${HEADERS})

target_include_directories(market_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
