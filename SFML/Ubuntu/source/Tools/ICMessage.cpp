#include "ICMessage.h"

ICMessage::ICMessage() {type = -1; args = new std::vector<int>(5);}
ICMessage::ICMessage(int type, std::vector<int> *args) : type(type), args(args) {}
ICMessage::~ICMessage() {delete [] args;}