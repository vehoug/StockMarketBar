#include "StockMarketBar/stock_market_bar.hpp"

int main()
{
    StockMarketBar stockMarketBar;
    while (true)
    {
        stockMarketBar.updatePrices();
        stockMarketBar.savePricesToJSON();
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
    return 0;
}