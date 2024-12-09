set(SOURCES
    OrderManager.cpp
)

set(HEADERS
    OrderManager.hpp
)

add_library(order_manager STATIC ${SOURCES} ${HEADERS})

target_include_directories(order_manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
