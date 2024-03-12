#include "gameeventhandler.h"
#include <QDebug>
#include "buildings/headquarters.h"
#include "buildings/farm.h"
#include "buildings/outpost.h"
#include "workers/farmer.hh"
#include "workers/lumberjack.hh"
#include "workers/miner.hh"
#include "workers/stonemason.hh"
#include "core/gameresourcemaps.hh"
#include "workers/basicworker.h"
#include "exceptions/illegalaction.h"
#include "exceptions/invalidpointer.h"
#include "buildings/fishinghut.hh"
#include "workers/fisher.h"
#include "workers/farmer.hh"
#include "workers/lumberjack.hh"
#include "buildings/employmentoffice.h"
#include "workers/stonemason.hh"

#include "buildings/mine.hh"
#include "buildings/quarry.hh"
#include "buildings/lumbermill.hh"



void GameEventHandler::endTurn()
{

    objectManager.lock()->generatePlayerResources(gameState.lock()->getCurrentPlayer().lock());
    objectManager.lock()->callSpecialActions(gameState.lock()->getCurrentPlayer().lock());

    bool turnEnded = gameState.lock()->endTurn();
    qDebug() <<  "Pelaajan vuoro:" << gameState.lock()->getCurrentPlayer().lock()->getName().c_str();
    if(turnEnded) {

        //kutsutaan pelaajan tilejä ja generoikakkaa


        mapWindow.lock()->updatePlayerContext(gameState.lock()->currentPlayer);
        mapWindow.lock()->setGameStateContext(gameState.lock());
        mapWindow.lock()->updateGameScene();

        mapWindow.lock()->updateProductionContext();

        mapWindow.lock()->resetCursorMode();
        bool gameEnded = objectManager.lock()->didGameEnd();

        if(gameEnded) {
            test->show();
            test->raise();
            test->activateWindow();
            test->setStats(gameState.lock()->getPlayers(), objectManager.lock()->getTiles());
        }

    } else {
        qDebug() << "vuoro ei loppunut";
    }

    qDebug() << "end turn end";

}

void GameEventHandler::saveGame()
{

    std::map<Course::ObjectId, std::shared_ptr<Course::TileBase>> m_tiles;
    std::map<std::string, std::vector<std::shared_ptr<Course::BuildingBase>>> m_buildings;
    std::map<std::string, std::vector<std::shared_ptr<Course::WorkerBase>>> m_workers;



    //Halutaan tilet, pelaajat, gameStatet
    //Obj manager m_tiles, m_

}

void GameEventHandler::initGameEventHandler(const std::shared_ptr<ObjectManager> &objMan,
                                            const std::shared_ptr<GameState> &gstate,
                                            const std::shared_ptr<MapWindow>& mapWindow)
{
    this->gameState = gstate;
    this->mapWindow = mapWindow;
    this->objectManager = objMan;
    this->test = nullptr;


    qDebug() << "EVENT HANDLER INIT";
}

bool GameEventHandler::playerHasFreWorkerSlots(const std::shared_ptr<Player> &player) {
    std::pair<int,int> workerData =getWorkerAvailability();
    return workerData.first < workerData.second;
}

std::pair<int, int> GameEventHandler::getWorkerAvailability()
{
      int workerLimit  = 0;
       int playerWorkerCount = 0;
    try {
       workerLimit = getCurrentPlayer()->getWorkerLimit();
       playerWorkerCount =  objectManager.lock()->getWorkers(getCurrentPlayer()).size();
    }

    catch(...) {

    }

      return std::pair<int,int>(playerWorkerCount, workerLimit);

}

void GameEventHandler::setGameInitialized(bool set) {
    isGameInitialized = set;
}

Course::ResourceMap GameEventHandler::getCurrentPlayerTotalProduction()
{

    return objectManager.lock()->getPlayersProductionTotal(gameState.lock()->getCurrentPlayer().lock());
}

void GameEventHandler::setEndDialog(DialogGameEnd *dialog)
{
    test = dialog;
}

GameEventHandler::GameEventHandler(): Course::iGameEventHandler()
{

}


bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> playerBase, Course::BasicResource resource, int amount)
{
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(playerBase);
    PlayerResource &playerResources = player->getResources();
    playerResources.at(resource) = playerResources.at(resource) + amount;
    return true;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> playerBase, Course::ResourceMap resources)
{
    qDebug() << "MODIFY RESOURCES!: tulluit varmaan generateResources pelaajalle, joka vuoron lopsusa";

    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(playerBase);

    PlayerResource &playerResources = player->getResources();

    qDebug() << "player resurssi ALUSSA: " << playerResources.at(Course::BasicResource::MONEY);
    Course::ResourceMap newresources = Course::mergeResourceMaps(resources,playerResources);
    playerResources = newresources;


    //tämä päivittää UI:n koska syyt

    return true;

}

bool GameEventHandler::subtractResources(std::shared_ptr<Course::PlayerBase> playerBase, Course::ResourceMap resources)
{
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(playerBase);
    PlayerResource &playerRes = player->getResources();

    qDebug() << "Recuding player res:" << player->getName().c_str();

    typedef Course::BasicResource res;

    qDebug() << "kultaa ennen: " << playerRes.find(res::MONEY)->second ;

    if (canSubtract(playerRes, resources)) {
        for (Course::ResourceMap::iterator it = resources.begin(); it != resources.end(); ++it) {
            Course::BasicResource key = it->first;
            int cost = it->second;

            playerRes.find(key)->second = playerRes.find(key)->second - cost;
        }

        qDebug() << "kultaa jälkeen :" << playerRes.find(res::MONEY)->second;

        return true;
    }

    qDebug() << "Resurssit eivät riittäneet rakentamiselle";
    return false;
}

bool GameEventHandler::canSubtract(PlayerResource& playerRes, Course::ResourceMap resourceCost)
{
    for (Course::ResourceMap::iterator it = resourceCost.begin(); it != resourceCost.end(); ++it) {
        Course::BasicResource key = it->first;
        int cost = it->second;

        if (playerRes.find(key)->second - cost < 0) {
            return false;
        }
    }

    return true;
}

bool GameEventHandler::gameInitialized()
{
    return isGameInitialized;
}

void GameEventHandler::resetCursorMode()
{
    mapWindow.lock()->resetCursorMode();
}

std::shared_ptr<Player> GameEventHandler::getCurrentPlayer() {
    return gameState.lock()->getCurrentPlayer().lock();
}


//TODO GENERALZISIISE, nyt hirveesti kutsuja samaan ja turhaan
Course::ObjectId GameEventHandler::constructBuilding(
                                         const std::shared_ptr<GameEventHandler>& ghandler,
                                         const std::shared_ptr<Player>& player,
                                         CursorInsertTarget buildTarget,
                                         const std::shared_ptr<Course::TileBase>& targetTile,
                                         std::string &message)
{

    Course::ObjectId newBuildingId = 0;
    try {

        //sallitaan vain yksi rakennus tilelle
        if(targetTile->getBuildingCount() != 0)
        {
            message = "Tile already has a buildign! Only one per tile allowed!";
            return NULL;
        }

        std::shared_ptr<Course::BuildingBase> building;
        Course::ResourceMap resourceCost;

        switch (buildTarget)
        {
            case CursorInsertTarget::FARM:
            {

                // Allow farms to be build only on own tiles. Neutral not allowed
                // Do this checking instead of COURSE Implemented Exceptions called on TileBase's addBuilding
                // To enforce our own game rules.
                if(targetTile->getOwner() != ghandler->getCurrentPlayer())
                {
                    message = "Tile is not owned by the player!";
                    return NULL;
                }


                Course::Farm *ptr = new Course::Farm( ghandler, objectManager.lock(), player);
                building = std::shared_ptr<Course::Farm>(ptr);
                resourceCost = Course::ConstResourceMaps::FARM_BUILD_COST;

            break;
            }


            case CursorInsertTarget::EMPLOYMENTOFFICE:
            {

                // Allow farms to be build only on own tiles. Neutral not allowed
                // Do this checking instead of COURSE Implemented Exceptions called on TileBase's addBuilding
                // To enforce our own game rules.
                if(targetTile->getOwner() != ghandler->getCurrentPlayer())
                {
                    message = "Tile is not owned by the player!";
                    return NULL;
                }
                EmploymentOffice *ptr = new EmploymentOffice( ghandler, objectManager.lock(), player);
                building = std::shared_ptr<EmploymentOffice>(ptr);
                resourceCost = Course::ConstResourceMaps::EMPLOYMENT_OFFICE_BUILD_COST;

            break;
            }

            case CursorInsertTarget::OUTPOST:
            {
                if(targetTile->getOwner() != nullptr)
                {
                    if(targetTile->getOwner() != ghandler->getCurrentPlayer())
                    {
                         message = "Outpost cannot be built on other players' tiles!";
                         return NULL;
                    }
                }

                Course::Outpost *ptr = new Course::Outpost( ghandler, objectManager.lock(), player);
                building = std::shared_ptr<Course::Outpost>(ptr);
                resourceCost = Course::ConstResourceMaps::OUTPOST_BUILD_COST;
                break;
            }

            case CursorInsertTarget::HEADQUARTERS:
            {
                if(targetTile->getOwner() != nullptr)
                {
                    if(targetTile->getOwner() != ghandler->getCurrentPlayer())
                    {
                         message = "Headquarters cannot be built on other players' tiles!";
                         return NULL;
                    }
                }
                Course::HeadQuarters *ptr = new Course::HeadQuarters( ghandler, objectManager.lock(), player);
                building = std::shared_ptr<Course::HeadQuarters>(ptr);
                resourceCost = Course::ConstResourceMaps::HQ_BUILD_COST;
                break;
            }

            case CursorInsertTarget::FISHINGHUT: {

                if(targetTile->getOwner() != ghandler->getCurrentPlayer())
                {
                    qDebug() << "virhe fishing Hut rakennuksessa";
                    message = "Tile is not owned by the player!";
                    return NULL;
                }
                    FishingHut *ptr = new FishingHut( ghandler, objectManager.lock(), player);
                    building = std::shared_ptr<FishingHut>(ptr);
                    resourceCost = Course::ConstResourceMaps::FH_BUILD_COST;

            break;
            }

        case CursorInsertTarget::MINE: {

            if(targetTile->getOwner() != ghandler->getCurrentPlayer())
            {
                message = "Tile is not owned by the player!";
                return NULL;
            }
                Mine *ptr = new Mine( ghandler, objectManager.lock(), player);
                building = std::shared_ptr<Mine>(ptr);
                resourceCost = Course::ConstResourceMaps::MINE_BUILD_COST;

        break;
        }

        case CursorInsertTarget::LUMBERMILL: {

            if(targetTile->getOwner() != ghandler->getCurrentPlayer())
            {
                message = "Tile is not owned by the player!";
                return NULL;
            }
                Lumbermill *ptr = new Lumbermill( ghandler, objectManager.lock(), player);
                building = std::shared_ptr<Lumbermill>(ptr);
                resourceCost = Course::ConstResourceMaps::LM_BUILD_COST;

        break;
        }

        case CursorInsertTarget::QUARRY: {

            if(targetTile->getOwner() != ghandler->getCurrentPlayer())
            {
                message = "Tile is not owned by the player!";
                return NULL;
            }
                Quarry *ptr = new Quarry( ghandler, objectManager.lock(), player);
                building = std::shared_ptr<Quarry>(ptr);
                resourceCost = Course::ConstResourceMaps::QUARRY_BUILD_COST;

        break;
        }

        }

        // if player has enough resources, build it
        if(getCurrentPlayer()->hasEnoughResourcesToBuild(resourceCost))
        {
            try
            {
                targetTile->addBuilding(building);
                mapWindow.lock()->updateWorkerLabels();
                mapWindow.lock()->updateWorkerButtons(getCurrentPlayer());
                targetTile->setOwner(ghandler->getCurrentPlayer());
                building->onBuildAction();
                objectManager.lock()->addBuilding(building, player);
                newBuildingId = building->ID;
                subtractResources(getCurrentPlayer(), resourceCost);
             }

            catch(Course::IllegalAction) {
                message = "Building cannot be placed on that tile!";
                return NULL;
            }
            catch(Course::InvalidPointer) {
                message = "Tile is not suitable for buildigns!";
                return NULL;
            }
            catch(...) {
                message = "Cannot do build action!";
                return NULL;
            }

        }
        else
        {
            message = "Not enough resources";
            return NULL;
        }

        //Set cursor mode back to normal

     }
    catch (...)

    {
        message = "Error in building action!";
        return NULL;
    }

    return newBuildingId;
}

void GameEventHandler::setGameEventMessage(std::string msg)
{
    mapWindow.lock()->setGameMessage(msg);
}







bool GameEventHandler::insertWorkerToTileForPlayer(const std::shared_ptr<Course::TileBase>& boundTile,
                                                   MapItem *targetTileItem,
                                                   const std::shared_ptr<Player> &player,
                                                   CursorInsertTarget selectedWorkerType,
                                                   const std::shared_ptr<Course::iGameEventHandler> &ghandlerPtr,
                                                   std::string &gameMessage  )
    {

    try {

    if(boundTile->getOwner() == player)
    {

            if(boundTile->hasSpaceForWorkers(1))
            {
                qDebug() << "Workerille on tilaa";
                     qDebug() << "worker type:" << selectedWorkerType;
                //luodaan worker

                     std::shared_ptr<Course::WorkerBase> worker;
                     switch (selectedWorkerType) {
                     case(CursorInsertTarget::MINER): {
                          worker = std::shared_ptr<Worker::Miner>
                                  (new Worker::Miner(ghandlerPtr, objectManager.lock(),
                                   std::dynamic_pointer_cast<Course::PlayerBase>(player)));
                          worker->setResourceFocus(Course::BasicResource::ORE);
                          break;
                     }

                     case(CursorInsertTarget::FARMER): {
                         worker = std::shared_ptr<Worker::Farmer>
                                 (new Worker::Farmer(ghandlerPtr, objectManager.lock(),
                                  std::dynamic_pointer_cast<Course::PlayerBase>(player)));
                         worker->setResourceFocus(Course::BasicResource::FOOD);
                         break;
                     }

                     case(CursorInsertTarget::LUMBERJACK): {
                         worker = std::shared_ptr<Worker::Lumberjack>
                                 (new Worker::Lumberjack(ghandlerPtr, objectManager.lock(),
                                  std::dynamic_pointer_cast<Course::PlayerBase>(player)));
                         worker->setResourceFocus(Course::BasicResource::WOOD);
                         break;
                     }

                     case(CursorInsertTarget::FISHER): {
                         worker = std::shared_ptr<Worker::Fisher>
                                 (new Worker::Fisher(ghandlerPtr, objectManager.lock(),
                                  std::dynamic_pointer_cast<Course::PlayerBase>(player)));
                         worker->setResourceFocus(Course::BasicResource::FOOD);
                         break;
                     }

                     case(CursorInsertTarget::STONEMASON): {
                         worker = std::shared_ptr<Worker::Stonemason>
                                 (new Worker::Stonemason(ghandlerPtr, objectManager.lock(),
                                  std::dynamic_pointer_cast<Course::PlayerBase>(player)));
                         worker->setResourceFocus(Course::BasicResource::STONE);
                         break;
                     }


                 } //switch end

                    objectManager.lock()->addWorker(worker, player);
                    boundTile->addWorker(worker);
                    mapWindow.lock()->updateWorkerLabels();
                    mapWindow.lock()->drawItem(worker, {CursorInsertMode::WORKER, selectedWorkerType}, targetTileItem);
                          return true;
                 } //if end
                else  {
                gameMessage = "No room for worker on that tile!";
                return false;
            }

        } //space for workers if end

        else
        {
            gameMessage = "Tile is not yours!";
            return false;
        }
   }
    catch(std::exception &e) {
        gameMessage = "Can't place worker on the target!";
        qDebug() << e.what();
    }

    return false;
}

