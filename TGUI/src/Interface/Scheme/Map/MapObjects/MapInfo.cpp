#include "MapInfo.h"
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>

sf::Vector2i MapInfo::mapSize = {10, 10};
int MapInfo::nBombs = 10;
std::vector<std::vector<tileInfo>> MapInfo::tiles;

int MapInfo::GenerateMap() {
    MapInfo::tiles = std::vector<std::vector<tileInfo>>(MapInfo::mapSize.x, std::vector<tileInfo>(MapInfo::mapSize.y, {-1, MapInfo::states::def}));

    // Generate <nBombs> random numbers, places for the bombs
    std::vector<int> numbers;
    for (int i = 0; i < MapInfo::mapSize.x * MapInfo::mapSize.y; i++) {
        numbers.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

    // Putting bombs in their places
    for (int i = 0; i < MapInfo::nBombs; i++) {
        int j = numbers[i];
        MapInfo::tiles[j / MapInfo::mapSize.x][j % MapInfo::mapSize.y].content = MapInfo::contents::bmb;
    }

    // Putting numbers
    int zeroCnt = 0;

    for (int i = 0; i < MapInfo::mapSize.x; i++) {
        for (int j = 0; j < MapInfo::mapSize.y; j++) {
            if (MapInfo::tiles[i][j].content == MapInfo::contents::bmb) continue;

            int cnt = 0;
            cnt += i > 0 && j > 0 && MapInfo::tiles[i - 1][j - 1].content == MapInfo::contents::bmb;
            cnt += i > 0 && MapInfo::tiles[i - 1][j].content == MapInfo::contents::bmb;
            cnt += i > 0 && j < MapInfo::mapSize.y - 1 &&
                   MapInfo::tiles[i - 1][j + 1].content == MapInfo::contents::bmb;
            cnt += j > 0 && MapInfo::tiles[i][j - 1].content == MapInfo::contents::bmb;
            cnt += j < MapInfo::mapSize.y - 1 && MapInfo::tiles[i][j + 1].content == MapInfo::contents::bmb;
            cnt += i < MapInfo::mapSize.x - 1 && j > 0 &&
                   MapInfo::tiles[i + 1][j - 1].content == MapInfo::contents::bmb;
            cnt += i < MapInfo::mapSize.x - 1 && MapInfo::tiles[i + 1][j].content == MapInfo::contents::bmb;
            cnt += i < MapInfo::mapSize.x - 1 && j < MapInfo::mapSize.y - 1 &&
                   MapInfo::tiles[i + 1][j + 1].content == MapInfo::contents::bmb;
            MapInfo::tiles[i][j].content = cnt;
            zeroCnt += cnt == 0;
        }
    }

    srand(time(nullptr));
    int highlightedNum = (rand() % zeroCnt) + 1;
    zeroCnt = 0;
    for (int i = 0; i < MapInfo::mapSize.x; i++) {
        for (int j = 0; j < MapInfo::mapSize.y; j++) {
            zeroCnt += MapInfo::tiles[i][j].content == 0;
            if (zeroCnt == highlightedNum) {
                MapInfo::tiles[i][j].state = MapInfo::states::highlighted;
                return 0;
            }
        }
    }
}