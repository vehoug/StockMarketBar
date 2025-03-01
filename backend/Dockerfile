# Use an official GCC-based image
FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Install dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    nlohmann-json3-dev \ 
    && rm -rf /var/lib/apt/lists/*

# Build the project
RUN mkdir -p build && cd build && cmake .. && make

# Run the price simulation
CMD ["./build/stock_market_bar"]