#include "Map.h"

#include <math.h>
#include <iostream>

#include "MapObjects/MapInfo.h"
#include "../../UIinformation.h"
#include "../../Time.h"
#include "DrawArray.h"
#include "MapObjects/Confetti.h"

sf::Texture Map::tiles;
tgui::Canvas * Map::canvas = nullptr;
sf::Vector2f Map::camera(0.0f, 0.0f);
std::vector<MapObject *> Map::objects;
float Map::height = 0.0f;
long long Map::timeBoom = 0;
std::vector<sf::Vector2f> Map::positionBoom;
bool Map::openTiles = false;
sf::Vector2f Map::openZeros = sf::Vector2f(-1.0f, -1.0f);

void Map::loadMap(tgui::Canvas * canvas) {

    positionBoom.clear();
    Map::openTiles = false;
    Map::openZeros = sf::Vector2f(-1.0f, -1.0f);
    positionBoom = std::vector<sf::Vector2f>(MapInfo::mapSize.x * MapInfo::mapSize.y);

    MapInfo::GenerateMap();

    Map::canvas = canvas;
    tiles.loadFromFile("../themes/images/button.png");
    DrawArray::setLayerTexture(0, &tiles);
    for (int i = 0; i < MapInfo::mapSize.x; i++) {
        for(int j = 0; j < MapInfo::mapSize.y; j++) {
            objects.emplace_back(new Tile(sf::Vector2f(32 * i, 32 * j), &MapInfo::tiles[i][j]));
        }
    }
    MapInfo::mapPos = canvas->getPosition();
    MapInfo::mouseOnMap = false;
    for(int i = 0; i < 2; i++) {
        MapInfo::pressedAfterPause[i] = 0;
    }
}

void Map::switchCase(sf::Vector2i task) {
    switch (MapInfo::mapState) {
        case MapInfo::playStates::waveCrazy:
            for (int i = task.x; i < task.y; i++) {
                Tile *tile = dynamic_cast<Tile *> (objects[i]);
                if (tile) {
                    sf::Vector2i ind = tile->info->pos;
                    sf::Vector2f pos = tile->pos;
                    tile->phi += Time::delta * 0.000001f;
                    float phi = tile->phi + ind.x * 0.3f;
                    DrawArray::update(tile->drawId,
                                      MapInfo::startPos + sf::Vector2f(ind) * 32.0f +
                                      sf::Vector2f(0.0f, 3.0f * (MapInfo::tiles[0].size() - 1 - ind.y)) * sin(phi));
                }
            }
            break;
        case MapInfo::playStates::wave:
            for (int i = task.x; i < task.y; i++) {
                Tile *tile = dynamic_cast<Tile *> (objects[i]);
                if (tile) {
                    sf::Vector2i ind = tile->info->pos;
                    tile->phi += Time::delta * 0.000005f;
                    float phi = tile->phi + ind.x * 0.3f;
                    DrawArray::update(tile->drawId,
                                      MapInfo::startPos + sf::Vector2f(ind) * 40.0f +
                                      sf::Vector2f(16.0f * sin(phi + 1.0f * ind.y), 16.0f * sin(phi)));
                }
            }
            break;
        case MapInfo::playStates::defeat:
            for (int i = task.x; i < task.y; i++) {
                Tile *tile = dynamic_cast<Tile *> (objects[i]);
                if (tile) {
                    float a = 0.000001f;
                    DrawArray::update(tile->drawId, tile->speed / a * (1.0f + float(-exp(a * (timeBoom - Time::time)))) + positionBoom[i]);
                }
            }
            break;
        case MapInfo::playStates::boom:
            for (int i = task.x; i < task.y; i++) {
                Tile *tile = dynamic_cast<Tile *> (objects[i]);
                if (tile) {
                    positionBoom[i] = DrawArray::getPos(tile->drawId);
                }
            }
            for (int i = task.x; i < task.y; i++) {
                Tile *tile = dynamic_cast<Tile *> (objects[i]);
                if (tile) {
                    sf::Vector2f delta = DrawArray::getPos(tile->drawId) - MapInfo::boomPos;
                    if (delta.x * delta.x + delta.y * delta.y < 3.0f) {
                        float phi = (rand() % 100) * 6.28f / 100.f;
                        tile->speed = sf::Vector2f(sin(phi), cos(phi)) * 0.0002f;
                    } else {
                        tile->speed = delta * (0.1f / (delta.x * delta.x + delta.y * delta.y));
                    }
                }
            }
            break;
        case MapInfo::playStates::win:
            break;
    }
}

void Map::updateObjects(sf::Vector2i task) {
    for(int i = task.x; i < task.y; i++) objects[i]->update(MapInfo::mapState);
}

void Map::update() {

    for(int i = 0; i < 2; i++) {
        if (MapInfo::pressedAfterPause[i] == 0 && !UIinformation::mPressed[i]) MapInfo::pressedAfterPause[i] = 1;
        if (MapInfo::pressedAfterPause[i] == 1 && UIinformation::mPressed[i]) MapInfo::pressedAfterPause[i] = 2;
    }

    if(UIinformation::wheel != 0 && MapInfo::mouseOnMap) {
        //printf("%f\n", UIinformation::wheel);
        height += -UIinformation::wheel * 0.01;
        if(height < -0.9f) height = -0.9f;
    }

    /*if(UIinformation::wheel != 0 && MapInfo::mouseOnMap) {
        //printf("%f\n", UIinformation::wheel);
        float dh = -UIinformation::wheel * 0.01;
        if(height + dh != 0) {
            height += dh;
            sf::Vector2f center = UIinformation::mPos - MapInfo::mapPos;
            //DrawArray::scroll(center, height, dh, H0)

            int DrawArray::scroll(sf::Vector2f center, float h, float dh, float H0) {
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < layers[i].getVertexCount(); j++) {
                        sf::Vertex &v = layers[i][j];
                        v.position = (v.position - center) * (H0 - h) / (H0 - h + dh) + center;
                    }
                }
                return 0;
            }

        }
    }*/

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
    float H0 = 1.0f;
    cameraMove -= UIinformation::mDeltaPressed[sf::Mouse::Left];
    sf::Transform trans;
    trans.scale(H0 / (height + H0) * sf::Vector2f(1.0f, 1.0f));
    sf::Vector2f size = canvas->getSize();
    sf::Vector2f center = camera - size / 2.0f * height / H0;
    trans.translate(-center);
    camera += cameraMove * (height + H0) / H0;

    canvas->clear(sf::Color::Black);

    for(int i = 0; i < 1; i++) {
        sf::RenderStates states;
        states.texture = DrawArray::textures[i];
        states.transform = trans;
        canvas->draw(DrawArray::layers[i], states);

        /*for(int j = 0; j < DrawArray::layers[i].getVertexCount(); j++) {
            DrawArray::layers[i][j].position = (DrawArray::layers[i][j].position - center) * H0 / (height + H0);
        }
        canvas->draw(DrawArray::layers[i], DrawArray::textures[i]);
        for(int j = 0; j < DrawArray::layers[i].getVertexCount(); j++) {
            DrawArray::layers[i][j].position = (DrawArray::layers[i][j].position * (height + H0) / H0) + center;
        }*/
    }

    for(int i = 1; i < 2; i++) {
        canvas->draw(DrawArray::layers[i], DrawArray::textures[i]);
    }

    MapInfo::mapPos = ((UIinformation::mPos - canvas->getPosition()) * (height + H0) / H0) + center;

    if(MapInfo::flagsCnt == 0 && MapInfo::nClosedTiles == 0) MapInfo::mapState = MapInfo::playStates::win;

    if (MapInfo::mapState != MapInfo::playStates::win && MapInfo::mapState != MapInfo::playStates::defeat)  {
        //run
        int n = UIinformation::coreAmount;
        sf::Thread * thr[n];
        int m = objects.size() / n;
        for(int i = 0; i < n; i++) {
            if(i == n - 1) {
                thr[i] = new sf::Thread(updateObjects, sf::Vector2i(m * i, objects.size()));
            } else {
                thr[i] = new sf::Thread(updateObjects, sf::Vector2i(m * i, m * (i + 1)));
            }
            thr[i]->launch();
        }
        for(int i = 0; i < n; i++) {
            thr[i]->wait();
            delete thr[i];
        }
    }

    MapInfo::UpdateCounters();

    switch (MapInfo::mapState) {
        case MapInfo::playStates::waveCrazy: {
            //run
            int n = UIinformation::coreAmount;
            sf::Thread *thr[n];
            int m = objects.size() / n;
            for (int i = 0; i < n; i++) {
                if(i == n - 1) {
                    thr[i] = new sf::Thread(switchCase, sf::Vector2i(m * i, objects.size()));
                } else {
                    thr[i] = new sf::Thread(switchCase, sf::Vector2i(m * i, m * (i + 1)));
                }
                thr[i]->launch();
            }
            for (int i = 0; i < n; i++) {
                thr[i]->wait();
                delete thr[i];
            }
            break;
        }
        case MapInfo::playStates::wave: {
            //run
            int n = UIinformation::coreAmount;
            sf::Thread *thr[n];
            int m = objects.size() / n;
            for (int i = 0; i < n; i++) {
                if(i == n - 1) {
                    thr[i] = new sf::Thread(switchCase, sf::Vector2i(m * i, objects.size()));
                } else {
                    thr[i] = new sf::Thread(switchCase, sf::Vector2i(m * i, m * (i + 1)));
                }
                thr[i]->launch();
            }
            for (int i = 0; i < n; i++) {
                thr[i]->wait();
                delete thr[i];
            }
            break;
        }
        case MapInfo::playStates::defeat: {
            if (MapInfo::timePauseStart > 0) timeBoom += Time::time - Time::delta - MapInfo::timePauseStart;
            if (Time::time - timeBoom > 5000000) timeBoom = Time::time - 5000000;
            if (UIinformation::mPressed[sf::Mouse::Right]) {
                timeBoom += 2 * Time::delta;
                if (timeBoom > Time::time) timeBoom = Time::time;
            }
            //run
            int n = UIinformation::coreAmount;
            sf::Thread *thr[n];
            int m = objects.size() / n;
            for (int i = 0; i < n; i++) {
                if(i == n - 1) {
                    thr[i] = new sf::Thread(switchCase, sf::Vector2i(m * i, objects.size()));
                } else {
                    thr[i] = new sf::Thread(switchCase, sf::Vector2i(m * i, m * (i + 1)));
                }
                thr[i]->launch();
            }
            for (int i = 0; i < n; i++) {
                thr[i]->wait();
                delete thr[i];
            }
            break;
        }
        case MapInfo::playStates::boom: {
            //run
            int n = UIinformation::coreAmount;
            sf::Thread *thr[n];
            int m = objects.size() / n;
            for (int i = 0; i < n; i++) {
                if(i == n - 1) {
                    thr[i] = new sf::Thread(switchCase, sf::Vector2i(m * i, objects.size()));
                } else {
                    thr[i] = new sf::Thread(switchCase, sf::Vector2i(m * i, m * (i + 1)));
                }
                thr[i]->launch();
            }
            for (int i = 0; i < n; i++) {
                thr[i]->wait();
                delete thr[i];
            }

            MapInfo::mapState = MapInfo::playStates::defeat;
            timeBoom = Time::time;
            break;
        }
        case MapInfo::playStates::win:
            Confetti::start(1, canvas->getSize()); //This checks was it started
            Confetti::update();
            break;
    }

    if(0 <= openZeros.x) {
        MapInfo::Q.push({(int) (openZeros.x / 32), (int) (openZeros.y / 32)});
        MapInfo::visited[(int) (openZeros.x / 32)][(int) (openZeros.y / 32)] = true;
    }
    openZeros = sf::Vector2f(-1.0f, -1.0f);
    MapInfo::OpenZeros();
    //run
    int n = UIinformation::coreAmount;
    sf::Thread *thr[n];
    int m = objects.size() / n;
    for (int i = 0; i < n; i++) {
        if(i == n - 1) {
            thr[i] = new sf::Thread(checkTileStates, sf::Vector2i(m * i, objects.size()));
        } else {
            thr[i] = new sf::Thread(checkTileStates, sf::Vector2i(m * i, m * (i + 1)));
        }
        thr[i]->launch();
    }
    for (int i = 0; i < n; i++) {
        thr[i]->wait();
        delete thr[i];
    }

    if(openTiles) {
        //run
        int n = UIinformation::coreAmount;
        sf::Thread *thr[n];
        int m = objects.size() / n;
        for (int i = 0; i < n; i++) {
            if(i == n - 1) {
                thr[i] = new sf::Thread(openAllTiles, sf::Vector2i(m * i, objects.size()));
            } else {
                thr[i] = new sf::Thread(openAllTiles, sf::Vector2i(m * i, m * (i + 1)));
            }
            thr[i]->launch();
        }
        for (int i = 0; i < n; i++) {
            thr[i]->wait();
            delete thr[i];
        }
    }
}

void Map::clean() {
    MapInfo::visited.clear();
    Confetti::clear();
    for(int i = 0; i < objects.size(); i++) delete objects[i];
    objects.clear();
    camera = sf::Vector2f(0.0f, 0.0f);
    canvas = nullptr;
    DrawArray::clear();
    for (int i = 0; i < MapInfo::mapSize.x; i++) {
        MapInfo::tiles[i].clear();
    }
    height = 0.0f;
    MapInfo::tiles.clear();
}

void Map::checkTileStates(sf::Vector2i task) {
    for (int i = task.x; i < task.y; i++) {
        if (((Tile *) objects[i])->info->content == 9) continue;
        if (((Tile *) objects[i])->info->state == MapInfo::states::pressed && ((Tile *) objects[i])->state != (Tile::ZERO + ((Tile *) objects[i])->info->content)) ((Tile *) objects[i])->changeState(Tile::ZERO + ((Tile *) objects[i])->info->content);
    }
}

void Map::openAllTiles(sf::Vector2i task) {
    for (int i = task.x; i < task.y; i++) {
        if (((Tile *) objects[i])->info->content == 9) {
            if (((Tile *) objects[i])->state == Tile::EXPLOSION || ((Tile *) objects[i])->info->state == MapInfo::states::flag) continue;
            ((Tile *) objects[i])->changeState(Tile::BOMB);
        } else {
            ((Tile *) objects[i])->changeState(((Tile *)objects[i])->info->state == MapInfo::states::flag ? Tile::BOMB_CROSSED  : Tile::ZERO + ((Tile *) objects[i])->info->content);
        }
    }

    for (int i = task.x ; i < task.y; i++) {
        if(i / MapInfo::mapSize.y < MapInfo::mapSize.y)
            MapInfo::tiles[i / MapInfo::mapSize.y][i % MapInfo::mapSize.y].state = MapInfo::states::pressed;
    }
}

void Map::win() {
    UIinformation::gui->get("PanelBG")->setVisible(false);
    UIinformation::gui->get("PanelBGEndGame")->setVisible(true);

    UIinformation::gui->get("WinMessage")->setVisible(true);

    UIinformation::gui->get("BombCounter")->setVisible(false);
    UIinformation::gui->get("MapSizeCounter")->setVisible(false);
    UIinformation::gui->get("TileCounter")->setVisible(false);
    UIinformation::gui->get("FlagCounter")->setVisible(false);
}

void Map::lose() {
    UIinformation::gui->get("PanelBG")->setVisible(false);
    UIinformation::gui->get("PanelBGEndGame")->setVisible(true);

    UIinformation::gui->get("LoseMessage")->setVisible(true);

    UIinformation::gui->get("BombCounter")->setVisible(false);
    UIinformation::gui->get("MapSizeCounter")->setVisible(false);
    UIinformation::gui->get("TileCounter")->setVisible(false);
    UIinformation::gui->get("FlagCounter")->setVisible(false);
}