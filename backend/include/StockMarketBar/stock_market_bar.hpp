#ifndef STOCK_MARKET_BAR_HPP
#define STOCK_MARKET_BAR_HPP

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <string>
#include <random>

class StockMarketBar
{
public:
    StockMarketBar();
    ~StockMarketBar() = default;

    void updatePrices();
    void savePricesToJSON();

private:
    std::mt19937 random_number_generator;
    std::uniform_real_distribution<double> step_distance;
    std::unordered_map<std::string, double> stock_prices;
    const std::string outputFile;

};

#endif // STOCK_MARKET_BAR_HPP