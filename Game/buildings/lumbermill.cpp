#include "lumbermill.hh"
#include "tiles/tilebase.h"
#include <QDebug>

Lumbermill::Lumbermill(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
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

std::string Lumbermill::getType() const
{
    return "Lumbermill";
}

bool Lumbermill::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return Course::PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and
            target->getType() != "Water" ;
}

void Lumbermill::doSpecialAction()
{
    if (currentLocationTile()->getType() == "Forest") {
        lockEventHandler()->modifyResource(getOwner(), Course::BasicResource::WOOD, 100);
    }
}


