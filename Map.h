#pragma once
#include <vector>

enum class TileType { Wall, Floor, Player, Enemy, Exit, Token };

class Map {
public:
    Map(int width, int height);

    TileType getTile(int x, int y) const;
    void setTile(int x, int y, TileType type);
    bool isWalkable(int x, int y) const;

    int getWidth() const;
    int getHeight() const;

    std::vector<std::pair<int, int>> getRoomCenters() const;

protected:
    std::vector<std::vector<TileType>> grid;
    std::vector<std::pair<int, int>> roomCenters;
};