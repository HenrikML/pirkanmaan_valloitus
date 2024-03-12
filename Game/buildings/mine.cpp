#include "mine.hh"
#include "tiles/tilebase.h"
#include <QDebug>

Mine::Mine(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
           const std::shared_ptr<Course::iObjectManager> &objectmanager,
           const std::shared_ptr<Course::PlayerBase> &owner,
           const int &tilespaces,
           const Course::ResourceMap &buildcost,
           const Course::ResourceMap &production):
    BuildingBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        buildcost,
        production
        )
{
}

std::string Mine::getType() const
{
    return "Mine";
}

bool Mine::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return Course::PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and
            target->getType() != "Water" ;
}
