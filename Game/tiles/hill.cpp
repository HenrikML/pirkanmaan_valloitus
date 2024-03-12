#include "hill.hh"
#include "gameeventhandler.h"

Hill::Hill(const Course::Coordinate &location,
           const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
           const std::shared_ptr<Course::iObjectManager> &objectmanager,
           const unsigned int& max_build,
           const unsigned int& max_work,
           const Course::ResourceMap& production):
    Course::TileBase(location,
                     eventhandler,
                     objectmanager,
                     max_build,
                     max_work,
                     production)
{

}

std::string Hill::getType() const
{
    return "Hill";
}

void Hill::addBuilding(const std::shared_ptr<Course::BuildingBase> &building)
{
    Course::TileBase::addBuilding(building);
    building->addHoldMarkers(1);
}

void Hill::removeBuilding(const std::shared_ptr<Course::BuildingBase> &building)
{
    Course::TileBase::removeBuilding(building);
}

void Hill::addWorker(const std::shared_ptr<Course::WorkerBase> &worker)
{
    Course::TileBase::addWorker(worker);
}

void Hill::removeWorker(const std::shared_ptr<Course::WorkerBase> &worker)
{
    Course::TileBase::removeWorker(worker);
}

