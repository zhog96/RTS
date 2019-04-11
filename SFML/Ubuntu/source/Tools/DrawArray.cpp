#include <source/UIObjects/UIinformation.h>
#include "DrawArray.h"

const int DrawArray::N = 3;

std::vector<sf::VertexArray> DrawArray::layers(N, sf::VertexArray(sf::Quads));
std::vector<sf::Texture *> DrawArray::textures(N, NULL);

sf::Vector2i DrawArray::addToLayer(sf::Vector2i _id,  sf::IntRect rectPos, sf::IntRect rectText) {
    int layer = _id.x;
    int id = _id.y;
    int a = 32;
    //sf::VertexBuffer triangles(sf::Triangles);
    if(id == 0) {
        layers[layer].append(sf::Vertex(sf::Vector2f(a * rectPos.left, a * rectPos.top), sf::Vector2f(a * rectText.left, a * rectText.top)));
        layers[layer].append(sf::Vertex(sf::Vector2f(a * (rectPos.left + rectPos.width), a * rectPos.top), sf::Vector2f(a * (rectText.left + rectText.width), a * rectText.top)));
        layers[layer].append(sf::Vertex(sf::Vector2f(a * (rectPos.left + rectPos.width), a * (rectPos.top + rectPos.height)), sf::Vector2f(a * (rectText.left + rectText.width), a * (rectText.top + rectText.height))));
        layers[layer].append(sf::Vertex(sf::Vector2f(a * rectPos.left, a * (rectPos.top + rectPos.height)), sf::Vector2f(a * rectText.left, a * (rectText.top + rectText.height))));
        return sf::Vector2i(layer, layers[layer].getVertexCount() / 4);
    } else {
        layers[layer][4 * (id - 1)] = (sf::Vertex(sf::Vector2f(a * rectPos.left, a * rectPos.top), sf::Vector2f(a * rectText.left, a * rectText.top)));
        layers[layer][4 * (id - 1) + 1] = (sf::Vertex(sf::Vector2f(a * (rectPos.left + rectPos.width), a * rectPos.top), sf::Vector2f(a * (rectText.left + rectPos.width), a * rectText.top)));
        layers[layer][4 * (id - 1) + 2] = (sf::Vertex(sf::Vector2f(a * (rectPos.left + rectPos.width), a * (rectPos.top + rectPos.height)), sf::Vector2f(a * (rectText.left + rectText.width), a * (rectText.top + rectText.height))));
        layers[layer][4 * (id - 1) + 3] = (sf::Vertex(sf::Vector2f(a * rectPos.left, a * (rectPos.top + rectPos.height)), sf::Vector2f(a * rectText.left, a * (rectText.top + rectText.height))));
        return sf::Vector2i(layer, 0);
    }
}

sf::Vector2i DrawArray::getPos(sf::Vector2i id) {
    return sf::Vector2i(layers[id.x][4 * (id.y - 1)].position);
}

int DrawArray::update(sf::Vector2i id, sf::Vector2f pos) {
    sf::Vector2f size = layers[id.x][4 * (id.y - 1) + 2].position - layers[id.x][4 * (id.y - 1)].position;
    layers[id.x][4 * (id.y - 1)].position = sf::Vector2f(pos);
    layers[id.x][4 * (id.y - 1) + 1].position = sf::Vector2f(pos) + sf::Vector2f(size.x, 0.f);
    layers[id.x][4 * (id.y - 1) + 2].position = sf::Vector2f(pos) + size;
    layers[id.x][4 * (id.y - 1) + 3].position = sf::Vector2f(pos) + sf::Vector2f(0.f, size.y);
}

sf::Vector2i DrawArray::addToLayer(sf::Vector2i _id, std::vector<sf::Vertex> &pos) {
    int layer = _id.x;
    int id = _id.y;
    if(id == 0) {
        for (int i = 0; i < 4; i++) {
            layers[layer].append(pos[i]);
        }
        return sf::Vector2i(layer, layers[layer].getVertexCount() / 4);
    } else {
        for(int i = 0; i < 4; i++) {
            layers[layer][(id - 1) + i] = pos[i];
        }
        return sf::Vector2i(layer, 0);
    }
}

int DrawArray::setLayerTexture(int layer, sf::Texture *texture) {
    textures[layer] = texture;
}

int DrawArray::draw() {
    for(int i = 0; i < N; i++)
        UIinformation::window->draw(layers[i], textures[i]);
}
