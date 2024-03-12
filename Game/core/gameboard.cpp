#include "gameboard.hh"
#include "core/worldgenerator.h"
#include <tiles/tilebase.h>
#include <vector>
#include "gamehandler.hh"
#include "core/coordinate.h"

Gameboard::Gameboard()
{

}

//
void Gameboard::createWorld(unsigned int size, GameHandler *gameHandler)
{
    for(unsigned int x = 0; x < size; ++x) {
    std::vector<Course::TileBase> inside;
         for(unsigned int y = 0; y < size; ++y) {
             Course::Coordinate coord(x,y);

             Course::TileBase tile(coord, gameHandler->getEventHandler(), gameHandler->getObjectManager(), 1, 1, {});
             inside.push_back(tile);
        //     qDebug() << "luotiin tile: [" << QString::number(x) << "] [" << QString::number(y) << "]";
         }
     //    qDebug() <<"tehtiin rivi: " << inside.size();
         newMap.push_back(inside);
     }
}

Map Gameboard::getGameboard()
{
    return world;
}
