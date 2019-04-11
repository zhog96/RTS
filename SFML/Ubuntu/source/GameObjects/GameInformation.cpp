#include "GameInformation.h"

std::vector< std::vector<Tile> > GameInformation::playMap(10, std::vector<Tile>(10));
std::vector< Unit > GameInformation::units;
std::vector< Building > GameInformation::buildings;
std::queue< ICMessage > IntCoreQ;
std::queue< ICMessage > CoreIntQ;