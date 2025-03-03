import React, { useEffect, useState } from "react";
import axios from "axios";
import "./StockMarketBar.css";

const API_URL = process.env.REACT_APP_API_URL || "http://api:5000/api/prices";

interface DrinkPrice {
  [key: string]: number;
}

interface DrinkTrend {
  [key: string]: string;
}

const StockMarketBar: React.FC = () => {
  const [prices, setPrices] = useState<DrinkPrice>({});
  const [prevPrices, setPrevPrices] = useState<DrinkPrice>({});
  const [trends, setTrends] = useState<DrinkTrend>({});
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const fetchPrices = async () => {
      try {
        const response = await axios.get(API_URL);
        setPrevPrices(prices);
        setPrices(response.data);

        const newTrends: DrinkTrend = {};
        Object.keys(response.data).forEach(drink => {
          const prevPrice = prevPrices[drink] || response.data[drink];
          newTrends[drink] = response.data[drink] > prevPrice ? "up" : response.data[drink] < prevPrice ? "down" : trends[drink] || "";
        });
        setTrends(newTrends);
      } catch (err) {
        console.error("Error fetching prices:", err);
        setError("Failed to fetch prices.");
      }
    };

    fetchPrices();
    const interval = setInterval(fetchPrices, 5000);
    return () => clearInterval(interval);
  }, [prices]);

  return (
    <div className="dashboard">
      <h1 className="title">Stock Market Bar</h1>
      {error ? (
        <p className="error">{error}</p>
      ) : (
        <table className="stock-table">
          <thead>
            <tr>
              <th>DRINK</th>
              <th>PRICE (NOK)</th>
            </tr>
          </thead>
          <tbody>
            {Object.entries(prices).map(([drink, price]) => (
              <tr key={drink} className={`price-row`}>
                <td>{drink}</td>
                  <td className={trends[drink] === "up" ? "price-up" : trends[drink] === "down" ? "price-down" : ""}>
                    <span className={trends[drink] === "up" ? "arrow-up" : trends[drink] === "down" ? "arrow-down" : "arrow-neutral"}>
                      {trends[drink] === "up" ? "▲ " : trends[drink] === "down" ? "▼ " : "- "}
                    </span>
                    {price.toFixed(2)}
                  </td>
              </tr>
            ))}
          </tbody>
        </table>
      )}
    </div>
  );
};

export default StockMarketBar;
