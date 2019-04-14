#pragma once



class ICMessage {
public:
    typedef enum {changeUnit, changeBuilding, endStep, movedUnit} typesI;
    typedef enum {actionError, moveUnit} typesC;
    int type;
    int id;
    int newState;
    int destination1;
    int destination2;
    ICMessage(int type, int id, int newState, int destination1, int destination2);
    ICMessage();
};