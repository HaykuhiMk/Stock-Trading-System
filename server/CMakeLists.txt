cmake_minimum_required(VERSION 3.27)
project(ServerPart)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
    ../src/limitOrder.cpp
    ../src/limitTrader.cpp
    ../src/marketOrder.cpp
    ../src/marketTrader.cpp
    ../src/order.cpp
    ../src/stock.cpp
    ../src/trader.cpp
    ./server.cpp
    ./main.cpp
    ./orderBook.cpp
    ./limitArchivedOrder.cpp
    ./archivedOrder.cpp
)

add_executable(ServerPart ${SOURCES})

target_link_libraries(ServerPart wsock32 ws2_32)
