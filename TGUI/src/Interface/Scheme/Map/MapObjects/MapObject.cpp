#include "MapObject.h"
#include "../DrawArray.h"
#include "../../../Time.h"
#include "../../../UIinformation.h"

sf::Vector2f MapObject::mapPos = sf::Vector2f(0.0f, 0.0f);

MapObject::MapObject(sf::Vector2f pos) {
    this->pos = pos;
    this->drawId = DrawArray::addToLayer(0, sf::IntRect((int) pos.x, (int) pos.y, 32, 32), sf::IntRect(0, 0, 32, 32));
    size = sf::Vector2f(32.0f, 32.0f);
}

void MapObject::solidMove(sf::Vector2f toPos) {
    pos = toPos;
    DrawArray::update(drawId, pos);
}

bool MapObject::mouseOn() {
    sf::Vector2f mPos = UIinformation::mPos - mapPos;
    if(pos.x + 1 <= mPos.x && pos.y + 1 <= mPos.y
    && mPos.x <= pos.x + size.x - 1 && mPos.y <= pos.y + size.y - 1) {
        return true;
    }
    return false;
}

bool MapObject::mouseLeftClickedOn() {
    return mouseOn() && UIinformation::mClicked[sf::Mouse::Left] && UIinformation::mDeltaClick[sf::Mouse::Left].x == 0 && UIinformation::mDeltaClick[sf::Mouse::Left].y == 0;
}

bool MapObject::mouseRightClickedOn() {
    return mouseOn() && UIinformation::mClicked[sf::Mouse::Right] && UIinformation::mDeltaClick[sf::Mouse::Right].x == 0 && UIinformation::mDeltaClick[sf::Mouse::Right].y == 0;
}

void MapObject::update() {
    printf("%d\n", 111);
}