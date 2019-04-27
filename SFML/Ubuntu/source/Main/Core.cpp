#include <source/GameObjects/GameInformation.h>
#include "Core.hpp"
#include <source/Tools/ICMessage.h>
#include "source/GameObjects/GameInformation.h"

bool Core::stopped = false;

int Core::initCore() {}

void processNextStep() {}

std::pair<int, int> processMovement(std::pair<int, int> from, std::pair<int, int> to) {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited(GameInformation::mapSize, std::vector<bool>(GameInformation::mapSize, false));
    std::vector<std::vector<std::pair<int, int>>> previousStep(GameInformation::mapSize, std::vector<std::pair<int, int>>(GameInformation::mapSize, {-1, -1}));
    queue.push(from);
    visited[from.first][from.second] = true;
    while (!queue.empty()) {
        std::pair<int, int> tile = queue.front();
        queue.pop();
        std::pair<int, int> nextTile = {tile.first + 1, tile.second};
        if (nextTile.first < GameInformation::mapSize && !visited[nextTile.first][nextTile.second] && !GameInformation::playMap[nextTile.first][nextTile.second].occupied) {
            queue.push(nextTile);
            visited[nextTile.first][nextTile.second] = true;
            previousStep[nextTile.first][nextTile.second] = tile;
        }
        nextTile = {tile.first - 1, tile.second};
        if (nextTile.first >= 0 && !visited[nextTile.first][nextTile.second] && !GameInformation::playMap[nextTile.first][nextTile.second].occupied) {
            queue.push(nextTile);
            visited[nextTile.first][nextTile.second] = true;
            previousStep[nextTile.first][nextTile.second] = tile;
        }

        nextTile = {tile.first, tile.second + 1};
        if (nextTile.second < GameInformation::mapSize && !visited[nextTile.first][nextTile.second] && !GameInformation::playMap[nextTile.first][nextTile.second].occupied) {
            queue.push(nextTile);
            visited[nextTile.first][nextTile.second] = true;
            previousStep[nextTile.first][nextTile.second] = tile;
        }

        nextTile = {tile.first, tile.second - 1};
        if (nextTile.second >= 0 && !visited[nextTile.first][nextTile.second] && !GameInformation::playMap[nextTile.first][nextTile.second].occupied) {
            queue.push(nextTile);
            visited[nextTile.first][nextTile.second] = true;
            previousStep[nextTile.first][nextTile.second] = tile;
        }
    }

    /*for (int i = 0; i < GameInformation::mapSize; i++) {
        for (int j = 0; j < GameInformation::mapSize; j++) {
            printf("{%d %d} ", previousStep[i][j].first, previousStep[i][j].second);
        }
        printf("\n");
    }*/
    //TODO print the entire map for debug, looks like it works, still cant be sure though

    if (previousStep[to.first][to.second].first == -1) {
        return {-1, -1};
    } else {
        std::pair<int, int> ret = to;
        while (previousStep[ret.first][ret.second] != from) ret = previousStep[ret.first][ret.second];
        return ret;
    }
}


int Core::processMessage(ICMessage * m) {
    switch (m->type) {
        case ICMessage::typesI::STOP: {
            stop();
            break;
        }
        case ICMessage::typesI::tryChangeUnit: { //Попытка что-то сделать с юнитом
            int xFrom = (*m->args)[0], yFrom = (*m->args)[1], xTo = (*m->args)[2], yTo = (*m->args)[3];
            int id;
            if (GameInformation::playMap[xFrom][yFrom].occupied) { //Проверяем, есть ли вообще юнит
                id = GameInformation::playMap[xFrom][yFrom].occupierId;
            } else {
                GameInformation::CoreIntQ.push(new ICMessage(ICMessage::typesC::actionError, NULL));
                break;
            }
            if (GameInformation::playMap[xTo][yTo].occupied) { //Проверяем, что хотят сделать -- если атака, то
                //либо это сразу атака, когда враг близко
                if ((xTo == xFrom + 1 && yTo == yFrom) || (xTo == xFrom - 1 && yTo == yFrom) || (xTo == xFrom && yTo == yFrom + 1) || (xTo == xFrom && yTo == yFrom - 1)) {
                    GameInformation::units[id].state = Unit::Attacking;
                    GameInformation::units[id].destination = {xTo, yTo};
                    //TODO
                } else {
                    //либо требуется немного пройти
                    GameInformation::units[id].state = Unit::Moving;
                    GameInformation::units[id].destination = {xTo, yTo};
                    std::pair<int, int> newXY = processMovement({xFrom, yFrom}, {xTo, yTo});
                    std::vector<int> *args = new std::vector<int>({xFrom, yFrom, newXY.first, newXY.second});
                    GameInformation::CoreIntQ.push(new ICMessage(ICMessage::typesC::moveUnit, args));
                    GameInformation::units[id].xy = newXY;
                    GameInformation::units[id].used = true;
                }
            } else {
                //если не атака, то просто идем
                GameInformation::units[id].state = Unit::Moving;
                GameInformation::units[id].destination = {xTo, yTo};
                std::pair<int, int> newXY = processMovement({xFrom, yFrom}, {xTo, yTo});
                std::vector<int> *args = new std::vector<int>({xFrom, yFrom, newXY.first, newXY.second});
                GameInformation::CoreIntQ.push(new ICMessage(ICMessage::typesC::moveUnit, args));
                GameInformation::units[id].xy = newXY;
                GameInformation::units[id].used = true;
            }
            break;
        }
        case ICMessage::typesI::endStep: {
            for (int i = 0; i < GameInformation::units.size(); i++) {
                GameInformation::units[i].used = false;
            }
            delete m;
            return 1;
        }
    }
    delete m;
    return 0;
}

int Core::run() {
    while(!stopped) {
        while (true) {
            if (!GameInformation::IntCoreQ.empty()) {
                ICMessage *m = GameInformation::IntCoreQ.front();
                GameInformation::IntCoreQ.pop();
                if (processMessage(m)) break;
            }
        }
        processNextStep();
    }
}

int Core::stop() {
    stopped = true;
}