#include "StockMarketBar/stock_market_bar.hpp"

using json = nlohmann::json;

#define STEP_DIST 0.3
#define EVENT_DIST 0.2
#define EVENT_TRIGGER_DIST 100
#define MOMENTUM_DIST 0.3

StockMarketBar::StockMarketBar() 
  : random_number_generator(std::random_device{}()), step_distance(-STEP_DIST, STEP_DIST),
    event_distance(-EVENT_DIST, EVENT_DIST), event_trigger_distance(0, EVENT_TRIGGER_DIST),
    momentum_distance(-MOMENTUM_DIST, MOMENTUM_DIST), tick_counter(0), 
    outputFile("/app/data/stock_prices.json") 
{
    drinks = 
    {
        {"Vodka Redbull", {30, 30, std::chrono::system_clock::now()}},
        {"Gin Tonic", {25, 25, std::chrono::system_clock::now()}},
        {"Storm Hard Seltzer", {35, 35, std::chrono::system_clock::now()}},
        {"Mojito", {25, 25, std::chrono::system_clock::now()}},
        {"Dahls Pilser 0.5L", {30, 30, std::chrono::system_clock::now()}},
        {"Schous Pilsner 0.5L", {40, 40, std::chrono::system_clock::now()}},
        {"Jaegermeister 25mL", {30, 30, std::chrono::system_clock::now()}},
        {"Rum & Coke", {20, 20, std::chrono::system_clock::now()}}
    };

    volatilities = 
    {
        {"Vodka Redbull", 0.4},
        {"Gin Tonic", 0.2},
        {"Storm Hard Seltzer", 0.1},
        {"Mojito", 0.3},
        {"Dahls Pilser 0.5L", 0.3},
        {"Schous Pilsner 0.5L", 0.05},
        {"Jaegermeister 25mL", 0.5},
        {"Rum & Coke", 0.4}
    };

    trends = 
    {
        {"Vodka Redbull", 0.0},
        {"Gin Tonic", 0.0},
        {"Storm Hard Seltzer", 0.0},
        {"Mojito", 0.0},
        {"Dahls Pilser 0.5L", 0.0},
        {"Schous Pilsner 0.5L", 0.0},
        {"Jaegermeister 25mL", 0.0},
        {"Rum & Coke", 0.0}
    };
}

void StockMarketBar::updatePrices()
{
    auto now = std::chrono::system_clock::now();

    for (auto& [drink, data] : drinks)
    {
        double trend_factor = trends.at(drink);
        double random_step = step_distance(random_number_generator) * volatilities.at(drink);;
        data.current_price += random_step + trend_factor;

        /* TODO: Min/max price hash map */
        data.current_price = std::clamp(data.current_price, static_cast<double>(15.0), static_cast<double>(50.0));

        auto duration = std::chrono::duration_cast<std::chrono::minutes>(now - data.last_updated).count();

        if (duration >= 60)
        {
            data.price_1h_ago = data.current_price;
            data.last_updated = now;
        } 
    } 

    tick_counter++;
    if (tick_counter % 20 == 0)
    {
        triggerEvent();
    }
}

void StockMarketBar::triggerEvent()
{
    int event_probability = event_trigger_distance(random_number_generator);
    
    if (event_probability < 20) 
    {
        /* Happy Hour event trigger */
        std::for_each(drink_prices.begin(), drink_prices.end(), [](std::pair<const std::string, double>& drink) 
        {
            drink.second *= 0.85;
            std::clamp(drink.second, static_cast<double>(15.0), static_cast<double>(50.0));
        });
    } else 
    {
        /* Prices spiking event trigger */
        std::for_each(drink_prices.begin(), drink_prices.end(), [](std::pair<const std::string, double>& drink) 
        {
            drink.second *= 1.15;
            std::clamp(drink.second, static_cast<double>(15.0), static_cast<double>(50.0));
        });
    }
}

void StockMarketBar::savePricesToJSON()
{
    std::ofstream file(outputFile);
    (!file) ? std::cerr << "Error opening file " << outputFile << '\n' :
    file << json(drink_prices).dump(4);
    file.close();
}