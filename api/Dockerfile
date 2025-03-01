# Use the .NET SDK for building the project
FROM mcr.microsoft.com/dotnet/sdk:7.0 AS build
WORKDIR /app

# Copy project files and restore dependencies
COPY . ./
RUN dotnet restore

# Build the project
RUN dotnet publish -c Release -o out

# Use a smaller .NET runtime image for running the app
FROM mcr.microsoft.com/dotnet/aspnet:7.0 AS runtime
WORKDIR /app

# Copy built application from the build stage
COPY --from=build /app/out .

# Expose port 5000
EXPOSE 5000

# Run the application
CMD ["dotnet", "StockMarketBarAPI.dll"]

