#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H
#include "interfaces/igameeventhandler.h"
#include "core/objectmanager.hh"
#include "graphics/mapwindow.hh"
#include "gamestate.h"
#include "tiles/tilebase.h"
#include <memory>

#include "buildings/buildingbase.h"
#include "graphics/mapitem.h"
#include "graphics/dialoggameend.h"

/**
 * @brief The GameEventHandler class handles player actions and events.
 */
class GameEventHandler: public Course::iGameEventHandler
{
public:

  //  static GameEventHandler &getInstance();
    int getData();
    int setData(int data);

    void endTurn();

    void saveGame();

    void initGameEventHandler(const std::shared_ptr<ObjectManager> &objMan,
                              const std::shared_ptr<GameState> &gstate,
                              const std::shared_ptr<MapWindow> &mapWindow );


    std::pair<int,int> getWorkerAvailability();

    Course::ResourceMap getCurrentPlayerTotalProduction();
    void setEndDialog(DialogGameEnd* dialog);

    ~GameEventHandler() = default;
    GameEventHandler();

private:

   bool isGameInitialized = false;
   DialogGameEnd *test;

    int data;

    // iGameEventHandler interface

public:
    bool modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount);
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources);

    bool subtractResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources);

    bool canSubtract(PlayerResource& playerRes, Course::ResourceMap resourceCost);

    bool gameInitialized();

    Course::ObjectId constructBuilding(
                           const std::shared_ptr<GameEventHandler>& ghandler,
                           const std::shared_ptr<Player>& player,
                           CursorInsertTarget buildingType,
                           const std::shared_ptr<Course::TileBase>& target,
                           std::string &message);



    void setGameEventMessage(std:: string msg);

    //nää privoiks

    std::weak_ptr<ObjectManager> objectManager;
    std::weak_ptr<GameState> gameState;
    std::weak_ptr<MapWindow> mapWindow;
    std::shared_ptr<Player> getCurrentPlayer();

    bool insertWorkerToTileForPlayer(const std::shared_ptr<Course::TileBase> &boundTile,
                                     MapItem *targetTileItem,
                                     const std::shared_ptr<Player> &player,
                                     CursorInsertTarget selectedWorkerType,
                                     const std::shared_ptr<Course::iGameEventHandler> &ghandlerPtr,
                                     std::string &gameMessage);



    void resetCursorMode();
    void setGameInitialized(bool set);
    bool playerHasFreWorkerSlots(const std::shared_ptr<Player> &player);
};

#endif // GAMEEVENTHANDLER_H
