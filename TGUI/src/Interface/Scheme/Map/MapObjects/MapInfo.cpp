#include "MapInfo.h"
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <queue>

sf::Vector2i MapInfo::mapSize = {40, 20};
int MapInfo::nBombs = 333;
int MapInfo::flagsCnt, MapInfo::nClosedTiles;


std::vector<std::vector<tileInfo>> MapInfo::tiles;
sf::Vector2f MapInfo::mapPos = sf::Vector2f(0.0f, 0.0f);
bool MapInfo::mouseOnMap = false;
int MapInfo::pressedAfterPause[2];

int MapInfo::GenerateMap() {
    MapInfo::tiles = std::vector<std::vector<tileInfo>>(MapInfo::mapSize.x, std::vector<tileInfo>(MapInfo::mapSize.y, {-1, MapInfo::states::def}));
    MapInfo::flagsCnt= MapInfo::nBombs;
    MapInfo::nClosedTiles = MapInfo::mapSize.x * MapInfo::mapSize.y - MapInfo::nBombs;

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
        MapInfo::tiles[j / MapInfo::mapSize.y][j % MapInfo::mapSize.y].content = MapInfo::contents::bmb;
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

int MapInfo::OpenZeros(sf::Vector2i start) {
    std::queue<sf::Vector2i> Q;
    std::vector<std::vector<bool>> visited(MapInfo::mapSize.x, std::vector<bool>(MapInfo::mapSize.y, false));
    Q.push(start);
    visited[start.x][start.y] = true;
    while (!Q.empty()) {
        sf::Vector2i cur = Q.front();
        int x = cur.x, y = cur.y;
        Q.pop();
        if (MapInfo::tiles[x][y].state == MapInfo::states::flag) continue;
        if (MapInfo::tiles[x][y].content != 0) {
            if (MapInfo::tiles[x][y].state != MapInfo::states::pressed) {
                MapInfo::tiles[x][y].state = MapInfo::states::pressed;
                MapInfo::nClosedTiles--;
                std::cout << "TILES LEFT : " << MapInfo::nClosedTiles << std::endl;
            }
            continue;
        }
        if (x > 0) {
            if (y > 0 && !visited[x-1][y-1]) {Q.push({x - 1, y - 1}); visited[x-1][y-1] = true;}
            if (y < MapInfo::mapSize.y - 1 && !visited[x-1][y+1]) {Q.push({x - 1, y + 1}); visited[x-1][y+1] = true;}
            if (!visited[x-1][y]) {Q.push({x - 1, y}); visited[x-1][y] = true;}
        }
        if (x < MapInfo::mapSize.x - 1) {
            if (y > 0 && !visited[x+1][y-1]) {Q.push({x + 1, y - 1}); visited[x+1][y-1] = true;}
            if (y < MapInfo::mapSize.y - 1 && !visited[x+1][y+1]) {Q.push({x + 1, y + 1}); visited[x+1][y+1] = true;}
            if (!visited[x+1][y]) {Q.push({x + 1, y}); visited[x+1][y] = true;}
        }
        if (y > 0 && !visited[x][y-1]) {Q.push({x, y - 1}); visited[x][y-1] = true;}
        if (y < MapInfo::mapSize.y - 1 && !visited[x][y+1]) {Q.push({x, y + 1}); visited[x][y+1] = true;}
        if (MapInfo::tiles[x][y].state != MapInfo::states::pressed) {
            MapInfo::tiles[x][y].state = MapInfo::states::pressed;
            MapInfo::nClosedTiles--;
            std::cout << "TILES LEFT : " << MapInfo::nClosedTiles << std::endl;
        }
    }
    for (int i = 0; i < MapInfo::mapSize.y; i++) {
        for (int j = 0; j < MapInfo::mapSize.x; j++) {
            std::cout << visited[j][i] << " ";
        }
        std::cout << std::endl;
    }
}