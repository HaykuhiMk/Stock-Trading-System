# Multi-Threaded Stock Trading System
The Stock Trading System is a software application designed to facilitate stock trading activities. It provides users with a platform for buying and selling stocks, tracking their portfolio, and making informed investment decisions.
This system offers a wide range of features and tools to simplify the stock trading process and enhance the user's overall experience. 

## Table of Contents

### ~ Features
### ~ Installation
### ~ How to Run the Program for Server
### ~ How to Run the Program for Client
### ~ Usage
### ~ Contributing

## Features
**User-Centric Design:** Our platform is built with the user in mind. It offers an intuitive and easy-to-navigate interface, ensuring that users can quickly access the tools they need to manage their stock portfolio efficiently.

**Real-time Stock Market Data:** The Stock Trading System provides access to real-time stock market data, including live stock prices, and trading volumes. Stay informed about market trends, news, and stock performance with up-to-the-minute data.

**Order Flexibility:** Execute trades with ease by choosing from various order types, including market orders and limit orders. This flexibility allows you to make precise buy and sell decisions according to your investment strategy.

**Data Analysis and Visualization:** Comprehensive data analysis tools and visualizations are available to help you make data-driven investment decisions.

**Open Source:** The Stock Trading System is an open-source project, which means that it is continuously evolving and open to contributions from the community.

## Installation
To set up the Stock Trading System on your local machine, follow these steps:

`git clone https://github.com/HaykuhiMk/Stock-Trading-System.git`

## How to Run the Program for Server
To execute the Multi-Threaded Stock Trading System for server, follow the steps below.

Prerequisites: Ensure that you have CMake and a compatible C++ compiler installed on your system.

### Option 1: Running with CMake 
1. Open a terminal or command prompt.

1. Navigate to the directory where you have downloaded or cloned the CPU-simulator repository.

1. Create a new directory called "build" for out-of-source builds:


#### `mkdir build`

  4. Move into the "build" directory:


#### `cd build`

  5. Generate the build files using CMake:


#### `cmake ..`

6. Build the project using the following command:


#### `cmake --build .`

7.Once the build process is complete, you can run the program by entering the following command:


#### `.\ServerPart.exe`

### Option 2: Running with Manual Compilation
1. Open a terminal or command prompt.

1. Navigate to the directory where you have downloaded or cloned the Stock-Trading-System repository.

1. Compile the source code files using the following command:

#### `g++ -std=c++11 -I./include ../src/limitOrder.cpp ../src/limitTrader.cpp ../src/marketOrder.cpp ../src/marketTrader.cpp ../src/order.cpp ../src/stock.cpp ../src/trader.cpp ./server.cpp ./main.cpp ./orderBook.cpp ./limitArchivedOrder.cpp ./archivedOrder.cpp -lws2_32 -o server`

Run the program by entering the following command:

#### `.\server.exe`

## How to Run the Program for Client
To execute the Multi-Threaded Stock Trading System for client, follow the steps below.

Prerequisites: Ensure that you have CMake and a compatible C++ compiler installed on your system.

### Option 1: Running with CMake 
1. Open a terminal or command prompt.

1. Navigate to the directory where you have downloaded or cloned the CPU-simulator repository.

1. Create a new directory called "build" for out-of-source builds:


#### `mkdir build`

4. Move into the "build" directory:


#### `cd build`

5. Generate the build files using CMake:


#### `cmake ..`

6. Build the project using the following command:


#### `cmake --build .`

7.Once the build process is complete, you can run the program by entering the following command:


#### `.\ClientPart.exe`

### Option 2: Running with Manual Compilation
1. Open a terminal or command prompt.

1. Navigate to the directory where you have downloaded or cloned the Stock-Trading-System repository.

1. Compile the source code files using the following command:

#### `g++ -std=c++11 -I./include ../src/limitOrder.cpp ../src/limitTrader.cpp ../src/marketOrder.cpp ../src/marketTrader.cpp ../src/order.cpp ../src/stock.cpp ../src/trader.cpp ./client.cpp ./main.cpp -lws2_32 -o client`

Run the program by entering the following command:

#### `.\client.exe`

## Usage

After launching the program, follow the on-screen instructions to interact with the system, place orders, and manage your stock portfolio.

## Contributing
If you want to contribute to this project, please follow these guidelines:

1. Fork the repository and create a new branch for your feature or bug fix.

1. Make your changes, test them thoroughly, and ensure that your code adheres to the project's coding standards.

1. Submit a pull request with a clear description of your changes, why they are needed, and any potential impact.
