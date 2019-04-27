#include "GameInformation.h"

std::vector< std::vector<Tile> > GameInformation::playMap(GameInformation::mapSize, std::vector<Tile>(GameInformation::mapSize));
std::vector< Unit > GameInformation::units;
std::vector< Building > GameInformation::buildings;
std::queue< ICMessage * > GameInformation::IntCoreQ;
std::queue< ICMessage * > GameInformation::CoreIntQ;
int GameInformation::mapSize = 32;