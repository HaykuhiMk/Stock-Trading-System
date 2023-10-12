cmake_minimum_required(VERSION 3.27)
project(ClientPart)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    ../src/limitOrder.cpp
    ../src/limitTrader.cpp
    ../src/marketOrder.cpp
    ../src/marketTrader.cpp
    ../src/order.cpp
    ../src/stock.cpp
    ../src/trader.cpp
    ./client.cpp
    ./main.cpp
)

include_directories(./include)

add_executable(ClientPart ${SOURCES})

target_link_libraries(ClientPart ws2_32)
