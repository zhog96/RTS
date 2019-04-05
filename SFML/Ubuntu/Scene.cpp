#include "Scene.hpp"

int Scene::getChange() {
    return changeTo;
}

Scene::Scene(sf::RenderWindow &window) : window(window){}
