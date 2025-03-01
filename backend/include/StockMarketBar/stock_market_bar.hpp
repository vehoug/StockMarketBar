#ifndef STOCK_MARKET_BAR_HPP
#define STOCK_MARKET_BAR_HPP

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include <random>

class StockMarketBar
{
public:
    StockMarketBar();
    ~StockMarketBar() = default;

    void updatePrices();
    void triggerEvent();
    void savePricesToJSON();

private:
    std::unordered_map<std::string, double> drink_prices;
    std::unordered_map<std::string, double> trends;
    std::unordered_map<std::string, double> volatilities;

    std::mt19937 random_number_generator;
    std::uniform_real_distribution<double> step_distance;
    std::uniform_real_distribution<double> event_distance;
    std::uniform_int_distribution<int> event_trigger_distance;
    std::uniform_real_distribution<double> momentum_distance;
    
    const std::string outputFile;
    int tick_counter;

};

#endif // STOCK_MARKET_BAR_HPP