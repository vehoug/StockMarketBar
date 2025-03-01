cmake_minimum_required(VERSION 3.10)
project(backend)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)

add_executable(backend src/main.cpp src/stock_market_bar.cpp)
target_include_directories(backend PRIVATE include)
target_link_libraries(backend PRIVATE nlohmann_json::nlohmann_json)