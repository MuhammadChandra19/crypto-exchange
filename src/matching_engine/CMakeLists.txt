set(SOURCES
    MatchingEngine.cpp
)

set(HEADERS
    MatchingEngine.hpp
)

add_library(matching_engine STATIC ${SOURCES} ${HEADERS})

target_include_directories(matching_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
