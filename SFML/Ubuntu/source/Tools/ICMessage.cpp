#include "ICMessage.h"

ICMessage::ICMessage() {}
ICMessage::ICMessage(int type, int id, int newState, int destination1, int destination2) : type(type), id(id), newState(newState), destination1(destination1), destination2(destination2) {}