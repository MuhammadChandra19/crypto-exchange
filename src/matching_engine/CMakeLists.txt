find_package(modern-cpp-kafka)

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
        main.cpp
)

add_library(matching_engine STATIC ${SOURCES} ${HEADERS})

target_include_directories(matching_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(matching_engine modern-cpp-kafka::modern-cpp-kafka)
