#include "Map.h"

Map::Map(int width, int height) {
    grid.resize(height, std::vector<TileType>(width, TileType::Wall));
}

TileType Map::getTile(int x, int y) const {
    if (x < 0 || x >= static_cast<int>(grid[0].size()) || y < 0 || y >= static_cast<int>(grid.size())) {
        return TileType::Wall; // Return Wall for out-of-bounds coordinates
    }
    return grid[y][x];
}

void Map::setTile(int x, int y, TileType type) {
    if (x >= 0 && x < static_cast<int>(grid[0].size()) && y >= 0 && y < static_cast<int>(grid.size())) {
        grid[y][x] = type;
    }
}

bool Map::isWalkable(int x, int y) const {
    TileType tile = getTile(x, y);
    return tile == TileType::Floor || tile == TileType::Player || 
           tile == TileType::Enemy || tile == TileType::Exit || 
           tile == TileType::Token;
}

int Map::getWidth() const {
    if (grid.empty()) {
        return 0;
    }
    return static_cast<int>(grid[0].size());
}

int Map::getHeight() const {
    return static_cast<int>(grid.size());
}

std::vector<std::pair<int, int>> Map::getRoomCenters() const {
    return roomCenters;
}
