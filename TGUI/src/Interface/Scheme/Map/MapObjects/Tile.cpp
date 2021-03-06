#include "Tile.h"
#include "../DrawArray.h"
#include "../../../UIinformation.h"
#include "../Map.h"
#include "../../../Time.h"
#include <queue>
#include <iostream>

Tile::Tile(sf::Vector2f pos, tileInfo * info) : MapObject(pos) , info(info), state(DEFAULT) {
    phi = 0.0f;
    speed = sf::Vector2f(0.0f, 0.0f);
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
            break;
        case BOMB_CROSSED:
            DrawArray::updateTexture(drawId, sf::Vector2i(1 * 32, 3 * 32));
            break;
        case EXPLOSION:
            DrawArray::updateTexture(drawId, sf::Vector2i(0 * 32, 3 * 32));
            break;
    }
    return 0;
}

void Tile::update(int par) {
    if(mouseLeftClickedOn()) {
        if (info->state == MapInfo::states::highlighted || info->state == MapInfo::states::def || info->state == MapInfo::states::qmark) {
            info->state = MapInfo::states::pressed;
            if (info->content == 9) {
                changeState(EXPLOSION);
                Map::lose();
                MapInfo::boomPos = DrawArray::getPos(drawId);
                MapInfo::mapState = MapInfo::playStates::boom;
                Map::openTiles = true;
                printf("%f %f\n", pos.x / 32, pos.y / 32);
            } else if (info->content == 0) {
                MapInfo::nClosedTiles--;
                std::cout << "TILES LEFT : " << MapInfo::nClosedTiles << std::endl;
                Map::openZeros = sf::Vector2f(pos.x, pos.y);
                printf("%f %f\n", pos.x / 32, pos.y / 32);
            } else {
                MapInfo::nClosedTiles--;
                std::cout << "TILES LEFT : " << MapInfo::nClosedTiles << std::endl;
                changeState(ZERO + info->content);
                printf("%f %f\n", pos.x / 32, pos.y / 32);
            }
        }
    }
    if (mouseRightClickedOn()) {
        if (info->state == MapInfo::states::highlighted || info->state == MapInfo::states::def) {
            if (MapInfo::flagsCnt > 0) {
                info->state = MapInfo::states::flag;
                changeState(FLAGGED);
                MapInfo::flagsCnt--;
                std::cout << "FLAGS LEFT : " << MapInfo::flagsCnt << std::endl;
            } else {
                info->state = MapInfo::states::qmark;
                changeState(QMARK);
            }
            printf("%f %f\n", pos.x / 32, pos.y / 32);
        } else if (info->state == MapInfo::states::flag) {
            info->state = MapInfo::states::qmark;
            changeState(QMARK);
            MapInfo::flagsCnt++;
            std::cout << "FLAGS LEFT : " << MapInfo::flagsCnt << std::endl;
            printf("%f %f\n", pos.x / 32, pos.y / 32);
        } else if (info->state == MapInfo::states::qmark) {
            info->state = MapInfo::states::def;
            changeState(DEFAULT);
            printf("%f %f\n", pos.x / 32, pos.y / 32);
        }
    }
    if (MapInfo::flagsCnt == 0 && MapInfo::nClosedTiles == 0) {
        MapInfo::mapState = MapInfo::playStates::win;
        Map::win();
    }
}