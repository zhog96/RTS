#include "Tile.h"
#include "../../../UIinformation.h"

Tile::Tile(sf::Vector2f pos) : MapObject(pos) {}

void Tile::update() {
    if(mouseClickedOn()) {
        printf("%f %f\n", pos.x / 32, pos.y / 32);
    }
}