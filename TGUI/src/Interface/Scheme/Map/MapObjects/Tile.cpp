#include "Tile.h"
#include "../DrawArray.h"
#include "../../../UIinformation.h"
#include "../Map.h"
#include <queue>

Tile::Tile(sf::Vector2f pos, tileInfo * info) : MapObject(pos) , info(info), state(DEFAULT) {
    if (info->state == MapInfo::states::highlighted) changeState(HIGHLIGHTED);
}

int Tile::changeState(int newState) {
    if (state == newState) return 0;
    state = newState;
    switch (state) {
        case DEFAULT:
            DrawArray::updateTexture(drawId, sf::Vector2i(0 * 32, 0 * 32));
            break;
        case FLAGGED:
            DrawArray::updateTexture(drawId, sf::Vector2i(0 * 32, 1 * 32));
            break;
        case QMARK:
            DrawArray::updateTexture(drawId, sf::Vector2i(0 * 32, 2 * 32));
            break;
        case EMPTY:
            DrawArray::updateTexture(drawId, sf::Vector2i(1 * 32, 0 * 32));
            break;
        case ZERO:
            DrawArray::updateTexture(drawId, sf::Vector2i(1 * 32, 2 * 32));
            break;
        case ONE:
            DrawArray::updateTexture(drawId, sf::Vector2i(2 * 32, 0 * 32));
            break;
        case TWO:
            DrawArray::updateTexture(drawId, sf::Vector2i(2 * 32, 1 * 32));
            break;
        case THREE:
            DrawArray::updateTexture(drawId, sf::Vector2i(2 * 32, 2 * 32));
            break;
        case FOUR:
            DrawArray::updateTexture(drawId, sf::Vector2i(3 * 32, 0 * 32));
            break;
        case FIVE:
            DrawArray::updateTexture(drawId, sf::Vector2i(3 * 32, 1 * 32));
            break;
        case SIX:
            DrawArray::updateTexture(drawId, sf::Vector2i(3 * 32, 2 * 32));
            break;
        case SEVEN:
            DrawArray::updateTexture(drawId, sf::Vector2i(4 * 32, 0 * 32));
            break;
        case EIGHT:
            DrawArray::updateTexture(drawId, sf::Vector2i(4 * 32, 1 * 32));
            break;
        case BOMB:
            DrawArray::updateTexture(drawId, sf::Vector2i(1 * 32, 1 * 32));
            break;
        case HIGHLIGHTED:
            DrawArray::updateTexture(drawId, sf::Vector2i(4 * 32, 2 * 32));
    }
    return 0;
}

void Tile::update() {
    if(mouseLeftClickedOn()) {
        if (info->state == MapInfo::states::highlighted || info->state == MapInfo::states::def || info->state == MapInfo::states::qmark) {
            info->state = MapInfo::states::pressed;
            if (info->content == 9) {
                changeState(BOMB);
                Map::openAllTiles();
                printf("%f %f\n", pos.x / 32, pos.y / 32);
            } else if (info->content == 0) {
                //changeState(ZERO);
                MapInfo::OpenZeros({(int) (pos.y / 32), (int) (pos.x / 32)});
                Map::checkTileStates();
                printf("%f %f\n", pos.x / 32, pos.y / 32);
                //openZeros(pos.x / 32, pos.y / 32);
            } else {
                changeState(ZERO + info->content);
                printf("%f %f\n", pos.x / 32, pos.y / 32);
            }
        }
    }
    if (mouseRightClickedOn()) {
        if (info->state == MapInfo::states::highlighted || info->state == MapInfo::states::def) {
            info->state = MapInfo::states::flag;
            changeState(FLAGGED);
            printf("%f %f\n", pos.x / 32, pos.y / 32);
        } else if (info->state == MapInfo::states::flag) {
            info->state = MapInfo::states::qmark;
            changeState(QMARK);
            printf("%f %f\n", pos.x / 32, pos.y / 32);
        } else if (info->state == MapInfo::states::qmark) {
            info->state = MapInfo::states::def;
            changeState(DEFAULT);
            printf("%f %f\n", pos.x / 32, pos.y / 32);
        }
    }
}
/*
void Tile::openZeros(int xx, int yy) {
    std::vector<std::vector<bool>> visited(MapInfo::mapSize.x, std::vector<bool>(MapInfo::mapSize.y, false));
    std::queue<sf::Vector2i> Q;
    Q.push({xx, yy});
    visited[xx][yy] = true;
    while (!Q.empty()) {
        sf::Vector2i cur = Q.front();
        int x = cur.x, y = cur.y;
        Q.pop();
        if (MapInfo::tiles[x][y].content != 0) continue;
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
        if (y > 0) {Q.push({x, y - 1}); visited[x][y-1] = true;}
        if (y < MapInfo::mapSize.y - 1) {Q.push({x, y + 1}); visited[x][y+1] = true;}
        Map::objects[x * MapInfo::mapSize.x + y]->changeState(ZERO);
        MapInfo::tiles[x][y].state = MapInfo::states::pressed;
    }
}*/