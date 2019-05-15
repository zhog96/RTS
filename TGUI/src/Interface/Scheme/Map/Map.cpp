#include "Map.h"

#include <math.h>

#include "../../UIinformation.h"
#include "../../Time.h"
#include "DrawArray.h"

sf::Texture Map::tiles;
tgui::Canvas * Map::canvas = nullptr;
sf::Vector2f Map::camera(0.0f, 0.0f);
std::vector<MapObject *> Map::objects;

void Map::loadMap(tgui::Canvas * canvas) {

    Map::canvas = canvas;
    tiles.loadFromFile("../themes/images/button.png");
    DrawArray::setLayerTexture(0, &tiles);
    for (int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            objects.emplace_back(new Tile(sf::Vector2f(32 * i, 32 * j)));
        }
    }

    MapObject::mapPos = canvas->getPosition();
}

void Map::update() {
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

    MapObject::mapPos = canvas->getPosition() + camera;

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
}