#include "objectmanager.hh"
#include "core/gameobject.h"
#include "tiles/tilebase.h"
#include "core/basicresources.h"
#include "core/resourcemaps.h"
#include "graphics/gamescene.h"
#include "workers/farmer.hh"
#include "workers/miner.hh"
#include "workers/stonemason.hh"
#include "workers/lumberjack.hh"
#include "core/resourcemaps.h"
#include <QDebug>
ObjectManager::ObjectManager()
{

}

void ObjectManager::setGameEventHandler(const std::shared_ptr<GameEventHandler> &ghandler)
{
    m_gameEventHandler = ghandler;
}


bool ObjectManager::didGameEnd() {

    bool gameEnded = true;
    for(auto tile : m_tiles) {
        if(tile.second->getOwner() == nullptr) {
            qDebug() << "ON OLEMASSA VIELÄ TYHJIÄ TILEJÄ.";
            gameEnded = false;
            break;
        }
    }
    return gameEnded;

}

Course::ResourceMap ObjectManager::getPlayersProductionTotal(const std::shared_ptr<Player>& player) {


     Course::ResourceMap total_production;
     //Loop all tiles player owns
     for (auto tile : m_tiles) {
         Course::ResourceMap tile_total_production;
         Course::ResourceMapDouble worker_efficiency;
         if(player == std::dynamic_pointer_cast<Player>(tile.second->getOwner())) {

             for(auto worker: tile.second->getWorkers())
             {
                  Course::ResourceMapDouble current_efficiency = worker->tileWorkAction();

                 worker_efficiency = mergeResourceMapDoubles(worker_efficiency, current_efficiency);
             }

             tile_total_production = multiplyResourceMap(tile.second->BASE_PRODUCTION, worker_efficiency);

             for( auto building : tile.second->getBuildings())
             {
                  Course::ResourceMap current_production = building->getProduction();
                  tile_total_production = mergeResourceMaps(tile_total_production, current_production);
             }
         }
         total_production = mergeResourceMaps(tile_total_production, total_production);
     }

    return total_production;





}

bool ObjectManager::generatePlayerResources(const std::shared_ptr<Player> &player)
{
    try
    {
    for (auto tile : m_tiles) {
        if(player == std::dynamic_pointer_cast<Player>(tile.second->getOwner())) {
            qDebug() << "TILE TYPE JOLLE RESURSSEJA" << tile.second->getType().c_str();
            tile.second->generateResources();
        }
    }
    }
    catch(...)
    {
        return false;
    }
    return true;


}

bool ObjectManager::callSpecialActions(const std::shared_ptr<Player> &player)
{
    std::vector<std::shared_ptr<Course::BuildingBase>> player_buildings = m_buildings.at(player->getName());

    for (std::shared_ptr<Course::BuildingBase> &building : player_buildings) {
        building->doSpecialAction();
    }

    std::vector<std::shared_ptr<Course::WorkerBase>> player_workers = m_workers.at(player->getName());

    for (std::shared_ptr<Course::WorkerBase> &worker : player_workers) {
        worker->doSpecialAction();
    }
    return true;
}

void ObjectManager::setPlayers(std::vector<std::shared_ptr<Player>> players)
{
    try {

    m_playerList = std::make_shared<std::vector<std::shared_ptr<Player>>>(players);
    for(std::shared_ptr<Player> player : players) {
        std::string name = player->getName();
        m_buildings[name] = {};
        m_workers[name] = {};
        qDebug() << "Laitetaan" << name.c_str()<< "mappiin";
    }
     }
    catch(...) {
        qDebug() << "Couldnt set players";
        return;
    }
}


void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    m_tiles_vector = tiles;
    for(std::shared_ptr<Course::TileBase> tile: tiles) {
        try {
            Course::ObjectId id = tile->ID;
            m_tiles[id] = tile;
        }
        catch(...) {
            qDebug() << "error adding tiles";
        }
    }
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    try {
        for(auto tile : m_tiles) {
            if(tile.second->getCoordinate().asQpoint() == coordinate.asQpoint()) {
                return tile.second;
            }
        }
    }
    catch(...)
    {
        qDebug() << "VIRHE!, ObjectManager::getTile error!";
    }

}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    return m_tiles.at(id);
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    qDebug() << "getting tiles";
    qDebug() << "COORDINAGTES:" << coordinates.size();



    std::vector<std::shared_ptr<Course::TileBase>> selectedTiles;

    for(auto tile : m_tiles) {
        for(auto coord : coordinates) {
            if(tile.second->getCoordinate().asQpoint() == coord.asQpoint()) {
                selectedTiles.push_back(tile.second);
            }
        }
    }
    qDebug() << "Palautetaan: " << selectedTiles.size();
    return selectedTiles;

}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles()
{
    return m_tiles_vector;
}

void ObjectManager::addBuilding(const std::shared_ptr<Course::BuildingBase> &building,  const std::shared_ptr<Player> &player)
{
    qDebug() << "Add Building" << building->getType().c_str() << "for player" << player->getName().c_str();
    m_buildings.at(player->getName()).push_back(building);

    //Add weak ptr to players object list
    player->addObject(building);

}

std::vector<std::shared_ptr<Course::BuildingBase> > ObjectManager::getBuildings(std::string player_name)
{
    return m_buildings.at(player_name);
}

void ObjectManager::addWorker(std::shared_ptr<Course::WorkerBase> worker, const std::shared_ptr<Player> &player)
{




    qDebug() << "adding worker for player: " << player->getName().c_str();
    m_workers.at(player->getName()).push_back(worker);

    player->addObject(worker);
}

std::shared_ptr<Course::BuildingBase> ObjectManager::getPlayerBuildingById(const std::shared_ptr<Player>& player, Course::ObjectId id)
{

    for(auto it : m_buildings.at(player->getName())) {
        if(it->ID == id) {
            qDebug() << "löyty object id:" << it->ID;
            return it;
        }
    }
}

std::vector<std::shared_ptr<Course::WorkerBase> > ObjectManager::getWorkers(const std::shared_ptr<Player> &player)
{
    return m_workers.at(player->getName());
}


