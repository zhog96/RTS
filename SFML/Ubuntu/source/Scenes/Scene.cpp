#include "Scene.hpp"

int Scene::getChange() {
    return changeTo;
}

Scene::Scene() {
    UIinformation::events = &events;
    changeTo = UIinformation::Scenes::NoAction;
}

Scene::~Scene() {
    for(int i = 0; i < uiobjects.size(); i++) {
        delete uiobjects[i];
    }
}