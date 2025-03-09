using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.IO;
using Newtonsoft.Json;

[ApiController]
[Route("api/prices")]
public class PricesController : ControllerBase
{
    private readonly string _filePath = "/app/data/stock_prices.json";

    public class DrinkPrice
    {
        public double Price { get; set; }
        public double PercentageChange { get; set; }
    }

    [HttpGet]
    public IActionResult GetPrices()
    {
        if (!System.IO.File.Exists(_filePath))
            return NotFound("Price data not available");

        var json = System.IO.File.ReadAllText(_filePath);
        var prices = JsonConvert.DeserializeObject<Dictionary<string, DrinkPrice>>(json);

        return Ok(prices);
    }
}
