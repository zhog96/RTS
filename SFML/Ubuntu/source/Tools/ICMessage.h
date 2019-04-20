#pragma once
#include <vector>


class ICMessage {
public:
    typedef enum {changeUnit, changeBuilding, endStep, movedUnit, STOP} typesI;
    typedef enum {actionError, moveUnit} typesC;
    int type;
    std::vector<int> *args;
    ICMessage(int type, std::vector<int> *args);
    ICMessage();
    ~ICMessage();
};