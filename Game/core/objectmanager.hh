#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

#include "interfaces/iobjectmanager.h"
#include "buildings/buildingbase.h"
#include "player.h"
#include "workers/workerbase.h"
#include <map>
#include "graphics/gamescene.h"
#include <memory>


/**
 * @brief The ObjectManager class handles object related information.
 */
class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager();

    /**
     * @brief Sets private m_gameEventHandler member variable.
     * @param ghandler is a const ref shared ptr to gameEventHanlder
     * @post Exception guarantee: Basic
     */
    void setGameEventHandler(const std::shared_ptr<GameEventHandler> & ghandler);

    virtual ~ObjectManager() = default;


    /**
     * @brief Sets players list and initializes their vectors for gameobjects and tiles.
     * @param players is a vector of pointers to all the players in game
     * @post Exception guarantee: Basic
     */
    void setPlayers(std::vector<std::shared_ptr<Player>> players);



    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles a vector that contains the Tiles to be added.
     * Exception Guarantee: Basic
     */
    virtual void addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles);


    /**
     * @brief Gets tile at given coordinate
     * @param coordinate of the tile to be given
     * @return TileBase Object of given coordinate
     * Exception Guarantee: Basic
     */
    virtual std::shared_ptr<Course::TileBase> getTile(const Course::Coordinate &coordinate);
    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId &id);


   /** @brief Gets all the tiles depiced by given coordinagtes.
    * @param coordinates to get tiles from
    * @return All Tiles for Given Coordinates
    * @post Exception guarantee: No guarantee.
    */

    virtual std::vector<std::shared_ptr<Course::TileBase> > getTiles(const std::vector<Course::Coordinate> &coordinates);

    /** @brief Gets all the tiles in the  game.
     * @return All tiles of the current game.
     * @post Exception guarantee: No guarantee.
     */
    std::vector<std::shared_ptr<Course::TileBase> > getTiles();

    /** @brief Adds a building for a player.
     * @param building pointer to a building of a building to be given
     * @param player target player
     * @post Exception guarantee: No guarantee.
     */
    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building,
                     const std::shared_ptr<Player> &player);

    /** @brief Returns buildings for a player
     * @param player_name name of the player to get all the buildings he has
     * @return Vector of all the buildings for player.
     * @post Exception guarantee: No guarantee.
     */
    std::vector<std::shared_ptr<Course::BuildingBase>> getBuildings(std::string player_name);

    /** @brief Adds a worker to given player
     * @param worker shared pointer to the worker
     * @param player constant reference pointer to the player
     * @post Exception guarantee: No guarantee.
     */
    void addWorker(std::shared_ptr<Course::WorkerBase> worker, const std::shared_ptr<Player> &player);


    /** @brief Gets pointer to a player's building of given gameobject ID.
     * @param player shared pointer to the worker
     * @param ID gameobject's unique ID number
     * @return Building of given ID of given player
     * @post Exception guarantee: No guarantee.
     */
    std::shared_ptr<Course::BuildingBase> getPlayerBuildingById(const std::shared_ptr<Player>& player,
                                                                Course::ObjectId ID);


    /** @brief Gets all the workers player has
     * @param player player to get all the workers from
     * @return All the workers player has
     * @pre setPlayers has to be called with valid  values
     * @post Exception guarantee: No guarantee.
     */
    std::vector<std::shared_ptr<Course::WorkerBase>> getWorkers(const std::shared_ptr<Player>& player);


    /** @brief Gets all the total production of the player.
     * @param player player to get the total productin for
     * @return ResourceMap of players production
     * @post Exception guarantee: No guarantee.
     */
    Course::ResourceMap getPlayersProductionTotal(const std::shared_ptr<Player> &player);

    /** @brief Calls TileBases generateResource function for all tiles player owns
     * @param player player to generate the resources for
     * @return Boolean if successfully generated
     * @post Exception guarantee: No guarantee.
     */
    bool generatePlayerResources(const std::shared_ptr<Player> &player);

    /** @brief Calls every worker and building's special action player owns
     * @param player call this players special action fro everything.
     * @return Boolean if succesfully called.
     * @pre setPlayers has to be called prior calling this.
     * @post Exception guarantee: No guarantee.
     */
    bool callSpecialActions(const std::shared_ptr<Player> &player);

    /** @brief Check function to call to check if game ended.
     * @return Boolean if game has ended.
     * @post Exception guarantee: No guarantee.
     */
    bool didGameEnd();

private:

    std::map<Course::ObjectId, std::shared_ptr<Course::TileBase>> m_tiles;
    std::weak_ptr<std::vector<std::shared_ptr<Player>>> m_playerList;
    std::weak_ptr<GameEventHandler> m_gameEventHandler;
    std::vector<std::shared_ptr<Course::TileBase>> m_tiles_vector;
    std::map<std::string, std::vector<std::shared_ptr<Course::BuildingBase>>> m_buildings;

    //Key is player's name, value is list of his workers
    std::map<std::string, std::vector<std::shared_ptr<Course::WorkerBase>>> m_workers;
};


#endif // OBJECTMANAGER_HH
