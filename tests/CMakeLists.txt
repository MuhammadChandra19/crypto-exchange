# Add Google Test
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Add test executable
add_executable(tests ${SOURCES}
    main.cpp
    LimitTests.cpp
    OrderbookTests.cpp
)

# Link libraries
target_link_libraries(tests PRIVATE
    gtest_main
    fmt
        matching_engine
)




# Enable testing
enable_testing()
add_test(NAME CryptoExchangeTests COMMAND tests)
