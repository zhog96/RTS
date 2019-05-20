#include <math.h>

#include "Confetti.h"
#include "MapInfo.h"

std::vector<sf::Vector2i> Confetti::confetti;
std::vector<sf::Vector2f> Confetti::confettiS;
int Confetti::layer;
sf::Vector2f Confetti::screenSize;
sf::Texture * Confetti::text = nullptr;
long long Confetti::lastImp;
long long Confetti::freq = 2500000;
bool Confetti::started = false;

void Confetti::start(int layer, sf::Vector2f screenSize) {
    if(!started) {
        text = new sf::Texture();
        text->loadFromFile("../themes/images/confetti.png");
        DrawArray::setLayerTexture(layer, text);
        Confetti::screenSize = screenSize;
        started = true;
        Confetti::layer = layer;
        lastImp = 0;
        float speed = 0.00001f;
        for (int i = 0; i < 1000; i++) {
            confetti.emplace_back(DrawArray::addToLayer(layer, sf::IntRect(0, int(screenSize.y), 4, 4),
                                                        sf::IntRect((rand() % 10) * 4, 0, 4, 4)));
            float phi = (rand() % 1000) * 3.14f / 2000.0f;
            confettiS.emplace_back((rand() % 100 + 10) * speed * sf::Vector2f(cos(phi), -sin(phi)));
        }
        for (int i = 0; i < 1000; i++) {
            confetti.emplace_back(DrawArray::addToLayer(layer, sf::IntRect(screenSize.x, int(screenSize.y), 4, 4),
                                                        sf::IntRect((rand() % 10) * 4, 0, 4, 4)));
            float phi = 3.14f - (rand() % 1000) * 3.14f / 2000.0f;
            confettiS.emplace_back((rand() % 100 + 10) * speed * sf::Vector2f(cos(phi), -sin(phi)));
        }
    }
}

void Confetti::update() {
    for(int i = 0; i < confetti.size(); i++) {
        DrawArray::update(confetti[i], DrawArray::getPos(confetti[i]) + confettiS[i] * float(Time::delta));
        DrawArray::upSize(confetti[i],  sf::Vector2f(1.0f, 1.0f) * (Time::delta * 0.00001f));
        confettiS[i].y += 0.000000001f * Time::delta;
    }
    if(freq <= lastImp) {
        lastImp = 0;
        float speed = 0.00001f;
        for (int i = 0; i < 1000; i++) {
            DrawArray::update(confetti[i], sf::Vector2f(0, screenSize.y));
            DrawArray::setSize(confetti[i], sf::Vector2f(4.0f, 4.0f));
            float phi = (rand() % 1000) * 3.14f / 2000.0f;
            confettiS[i] = ((rand() % 100 + 10) * speed * sf::Vector2f(cos(phi), -sin(phi)));
        }
        for (int i = 0; i < 1000; i++) {
            DrawArray::update(confetti[1000 + i], sf::Vector2f(screenSize.x, int(screenSize.y)));
            DrawArray::setSize(confetti[1000 + i], sf::Vector2f(4.0f, 4.0f));
            float phi = 3.14f - (rand() % 1000) * 3.14f / 2000.0f;
            confettiS[1000 + i] = ((rand() % 100 + 10) * speed * sf::Vector2f(cos(phi), -sin(phi)));
        }
    }
    lastImp += Time::delta;
}

void Confetti::clear() {
    if(started) {
        started = false;
        delete text;
        text = nullptr;
        DrawArray::layers[layer].clear();
        confetti.clear();
        confettiS.clear();
    }
}