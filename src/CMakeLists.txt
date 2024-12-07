add_subdirectory(matching_engine)
add_subdirectory(order_manager)
add_subdirectory(market_data)

set(SOURCES
    main.cpp
)

add_executable(CryptoExchange ${SOURCES})

target_link_libraries(CryptoExchange
    PRIVATE matching_engine
    PRIVATE order_manager
    PRIVATE market_data
    PRIVATE fmt
)

target_include_directories(CryptoExchange PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
