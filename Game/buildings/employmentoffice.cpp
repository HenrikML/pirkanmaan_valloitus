#include "employmentoffice.h"
#include "tiles/tilebase.h"
#include <QDebug>


#include "core/playerbase.h"
#include "player.h"

EmploymentOffice::EmploymentOffice(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
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

std::string EmploymentOffice::getType() const
{
    return "EmploymentOffice";
}

bool EmploymentOffice::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return Course::PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and
            target->getType() != "Water" ;
}



void EmploymentOffice::onBuildAction()
{
    std::dynamic_pointer_cast<Player>(getOwner())->modifyWorkerLimit(5);
    Course::BuildingBase::onBuildAction();
}
