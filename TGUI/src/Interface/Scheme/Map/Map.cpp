#include "Map.h"

#include <math.h>
#include <iostream>

#include "MapObjects/MapInfo.h"
#include "../../UIinformation.h"
#include "../../Time.h"
#include "DrawArray.h"

sf::Texture Map::tiles;
tgui::Canvas * Map::canvas = nullptr;
sf::Vector2f Map::camera(0.0f, 0.0f);
std::vector<MapObject *> Map::objects;

void Map::loadMap(tgui::Canvas * canvas) {

    MapInfo::GenerateMap();

    Map::canvas = canvas;
    tiles.loadFromFile("../themes/images/button.png");
    DrawArray::setLayerTexture(0, &tiles);
    for (int i = 0; i < MapInfo::mapSize.x; i++) {
        for(int j = 0; j < MapInfo::mapSize.y; j++) {
            objects.emplace_back(new Tile(sf::Vector2f(32 * i, 32 * j), &MapInfo::tiles[j][i]));
        }
    }
    MapInfo::mapPos = canvas->getPosition();


}

void Map::update() {
    if(canvas->getPosition().x <= UIinformation::mPos.x && canvas->getPosition().y <= UIinformation::mPos.y &&
            UIinformation::mPos.x <= canvas->getPosition().x + canvas->getSize().x &&
            UIinformation::mPos.y <= canvas->getPosition().y + canvas->getSize().y) {
        MapInfo::mouseOnMap = true;
    } else {
        MapInfo::mouseOnMap = false;
    }

    sf::Vector2f cameraMove(0.0f, 0.0f);
    float cameraMoveSpeed = 0.001f;
    if(UIinformation::bPressed[sf::Keyboard::Left]) cameraMove.x += -1.0f;
    if(UIinformation::bPressed[sf::Keyboard::Right]) cameraMove.x += 1.0f;
    if(UIinformation::bPressed[sf::Keyboard::Down]) cameraMove.y += 1.0f;
    if(UIinformation::bPressed[sf::Keyboard::Up]) cameraMove.y += -1.0f;

    if(cameraMove.x * cameraMove.x + cameraMove.y * cameraMove.y != 0)
        cameraMove = cameraMove / sqrt(cameraMove.x * cameraMove.x + cameraMove.y * cameraMove.y);
    cameraMove *= cameraMoveSpeed * Time::delta;
    cameraMove -= UIinformation::mDeltaPressed[sf::Mouse::Left];
    camera -= cameraMove;

    MapInfo::mapPos = canvas->getPosition() + camera;

    canvas->clear(sf::Color::Black);

    sf::View view;
    view.setSize(sf::Vector2f(1000.f, 1000.f));
    for(int i = 0; i < DrawArray::N; i++) {
        for(int j = 0; j < DrawArray::layers[i].getVertexCount(); j++)
            DrawArray::layers[i][j].position += camera;
        canvas->draw(DrawArray::layers[i], DrawArray::textures[i]);
        for(int j = 0; j < DrawArray::layers[i].getVertexCount(); j++)
            DrawArray::layers[i][j].position -= camera;
    }

    for(int i = 0; i < objects.size(); i++) objects[i]->update();
}

void Map::clean() {
    for(int i = 0; i < objects.size(); i++) delete objects[i];
    objects.clear();
    camera = sf::Vector2f(0.0f, 0.0f);
    canvas = nullptr;
    DrawArray::clear();
    for (int i = 0; i < MapInfo::mapSize.x; i++) {
        MapInfo::tiles[i].clear();
    }
    MapInfo::tiles.clear();
}

void Map::checkTileStates() {
    for (int i = 0; i < objects.size(); i++) {
        if (((Tile *) objects[i])->info->content == 9) continue;
        if (((Tile *) objects[i])->info->state == MapInfo::states::pressed && ((Tile *) objects[i])->state != (Tile::ZERO + ((Tile *) objects[i])->info->content)) ((Tile *) objects[i])->changeState(Tile::ZERO + ((Tile *) objects[i])->info->content);
    }
}