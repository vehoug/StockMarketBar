cmake_minimum_required(VERSION 3.10)
project(stock_market_bar)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)

add_executable(stock_market_bar src/main.cpp src/stock_market_bar.cpp)
target_include_directories(stock_market_bar PRIVATE include)
target_link_libraries(stock_market_bar PRIVATE nlohmann_json::nlohmann_json)