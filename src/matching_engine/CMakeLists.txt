set(SOURCES
    MatchingEngine.cpp
    Order.cpp
    Limit.cpp
    Match.cpp
    Orderbook.cpp
)

set(HEADERS
    MatchingEngine.hpp
    Order.hpp
    Limit.hpp
    Match.hpp
    Orderbook.hpp
)

add_library(matching_engine STATIC ${SOURCES} ${HEADERS})

target_include_directories(matching_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
