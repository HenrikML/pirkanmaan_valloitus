#include "gamehandler.hh"

GameHandler::GameHandler()
{

}

ObjectManager *GameHandler::getObjectManager()
{
    return &objectManager;
}

EventHandler *GameHandler::getEventHandler()
{
    return &objectManager;
}
