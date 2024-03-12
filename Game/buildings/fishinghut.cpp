#include "fishinghut.hh"
#include "tiles/tilebase.h"
#include <QDebug>

FishingHut::FishingHut(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
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

std::string FishingHut::getType() const
{
    return "FishingHut";
}

bool FishingHut::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return Course::PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and
            target->getType() == "Water";
}

void FishingHut::doSpecialAction()
{
    //lockEventHandler()->modifyResource(getOwner(), Course::BasicResource::FOOD, 5000);
}

