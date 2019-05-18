#include "MapObject.h"
#include "../DrawArray.h"
#include "../../../Time.h"
#include "../../../UIinformation.h"
#include "MapInfo.h"

MapObject::MapObject(sf::Vector2f pos) {
    this->pos = pos;
    this->drawId = DrawArray::addToLayer(0, sf::IntRect((int) pos.x, (int) pos.y, 32, 32), sf::IntRect(0, 0, 32, 32));
}

void MapObject::solidMove(sf::Vector2f toPos) {
    pos = toPos;
    DrawArray::update(drawId, pos);
}

bool MapObject::mouseOn() {
    sf::Vector2f mPos = MapInfo::mapPos;
    sf::Vector2i size = DrawArray::getSize(drawId);
    if(MapInfo::mouseOnMap
    && pos.x <= mPos.x && pos.y <= mPos.y
    && mPos.x <= pos.x + size.x - 1 && mPos.y <= pos.y + size.y - 1) {
        return true;
    }
    return false;
}

bool MapObject::mouseLeftClickedOn() {
    return mouseOn() && MapInfo::pressedAfterPause[sf::Mouse::Left] == 2 && UIinformation::mClicked[sf::Mouse::Left] && UIinformation::mDeltaClick[sf::Mouse::Left].x == 0 && UIinformation::mDeltaClick[sf::Mouse::Left].y == 0;
}

bool MapObject::mouseRightClickedOn() {
    return mouseOn() && MapInfo::pressedAfterPause[sf::Mouse::Right] == 2 && UIinformation::mClicked[sf::Mouse::Right] && UIinformation::mDeltaClick[sf::Mouse::Right].x == 0 && UIinformation::mDeltaClick[sf::Mouse::Right].y == 0;
}

void MapObject::update() {
    printf("%d\n", 111);
}