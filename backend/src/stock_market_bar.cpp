#include "StockMarketBar/stock_market_bar.hpp"

using json = nlohmann::json;

#define STEP_DIST 0.1
#define EVENT_DIST 0.2
#define EVENT_TRIGGER_DIST 100
#define MOMENTUM_DIST 0.3

StockMarketBar::StockMarketBar() 
  : random_number_generator(std::random_device{}()), step_distance(-STEP_DIST, STEP_DIST),
    event_distance(-EVENT_DIST, EVENT_DIST), event_trigger_distance(0, EVENT_TRIGGER_DIST),
    momentum_distance(-MOMENTUM_DIST, MOMENTUM_DIST), tick_counter(0), 
    outputFile("/app/data/stock_prices.json") 
{
    drink_prices = 
    {
        {"vodka_redbull", 30},
        {"gin_tonic", 25},
        {"storm", 35}
    };

    volatilities = 
    {
        {"vodka_redbull", 0.1},
        {"gin_tonic", 0.2},
        {"storm", 0.3}
    };
}

void StockMarketBar::updatePrices()
{
    for (auto& [drink, price] : drink_prices)
    {
        double trend_factor = trends.at(drink);
        double random_step = step_distance(random_number_generator) * volatilities.at(drink);;
        price += random_step + trend_factor;

        /* TODO: Min/max price hask map */
        price = std::clamp(price, 15, 50);
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
        std::for_each(drink_prices.begin(), drink_prices.end(), [](std::pair<const std::string, double>& drink) 
        {
            drink.second *= 0.85;
        });
    } else 
    {
        std::for_each(drink_prices.begin(), drink_prices.end(), [](std::pair<const std::string, double>& drink) 
        {
            drink.second *= 1.15;
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