#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include "radialBasisFunctionInterpolation.h"

// ── Parse canada_nodes.csv ─────────────────────────────────────
void loadData(const std::string& filename,
              std::vector<Point>& nodes,
              Vector& values)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + filename);

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string lat_s, lon_s, val_s;
        std::getline(ss, lat_s, ',');
        std::getline(ss, lon_s, ',');
        std::getline(ss, val_s, ',');
        nodes.push_back({std::stod(lat_s), std::stod(lon_s)});
        values.push_back(std::stod(val_s));
    }
}

// ── Write evaluation grid to CSV ───────────────────────────────
void saveGrid(const std::string& filename,
              const std::vector<double>& lats,
              const std::vector<double>& lons,
              const std::vector<std::vector<double>>& grid)
{
    std::ofstream file(filename);
    file << "latitude,longitude,temp_c\n";
    for (size_t i = 0; i < lats.size(); ++i)
        for (size_t j = 0; j < lons.size(); ++j)
            file << std::fixed << std::setprecision(4)
                 << lats[i] << "," << lons[j] << ","
                 << grid[i][j] << "\n";
    std::cout << "Grid saved to " << filename << "\n";
}

int main()
{
    // ── 1. Load station data ───────────────────────────────────
    std::vector<Point> nodes;
    Vector values;
    loadData("canada_nodes.csv", nodes, values);
    std::cout << "Loaded " << nodes.size() << " stations.\n";

    // ── 2. Build kernel matrix and solve ──────────────────────
    Matrix distMatrix   = euclideanDistanceMatrixGenerator(nodes);
    Matrix kernelMatrix = radialKernelMatrixGenerator(distMatrix);
    Vector lambdas      = gaussianEliminationPivot(kernelMatrix, values);
    std::cout << "System solved. Lambda vector size: " << lambdas.size() << "\n";

    // ── 3. Evaluate on a grid over Canada ─────────────────────
    // Bounding box: lat [42.0, 83.0], lon [-141.0, -52.0]
    int gridRes = 50;
    std::vector<double> latGrid(gridRes), lonGrid(gridRes);

    double latMin = 42.0,   latMax = 83.0;
    double lonMin = -141.0, lonMax = -52.0;

    for (int i = 0; i < gridRes; ++i) {
        latGrid[i] = latMin + i * (latMax - latMin) / (gridRes - 1);
        lonGrid[i] = lonMin + i * (lonMax - lonMin) / (gridRes - 1);
    }

    std::vector<std::vector<double>> grid(gridRes, std::vector<double>(gridRes));
    for (int i = 0; i < gridRes; ++i) {
        for (int j = 0; j < gridRes; ++j) {
            Point p = {latGrid[i], lonGrid[j]};
            grid[i][j] = RBFInterpolant(p, nodes, lambdas, /*epsilon=*/0.5);
        }
    }
    std::cout << "Grid evaluated (" << gridRes << "x" << gridRes << " points).\n";

    // ── 4. Save results ───────────────────────────────────────
    saveGrid("canada_grid.csv", latGrid, lonGrid, grid);

    // ── 5. Print station summary ──────────────────────────────
    std::cout << "\nStation summary (first 10):\n";
    std::cout << std::left
              << std::setw(10) << "Lat"
              << std::setw(12) << "Lon"
              << "Avg Temp (C)\n";
    std::cout << std::string(34, '-') << "\n";
    for (size_t i = 0; i < std::min(nodes.size(), size_t(10)); ++i)
        std::cout << std::fixed << std::setprecision(4)
                  << std::setw(10) << nodes[i][0]
                  << std::setw(12) << nodes[i][1]
                  << values[i] << "\n";

    return 0;
}
