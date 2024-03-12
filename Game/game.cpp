#include "game.h"
#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "buildings/farm.h"
#include "tiles/hill.hh"
#include "tiles/swamp.h"
#include "tiles/water.hh"
#include "tiles/desert.h"

#include "QDebug"
#include "core/playerbase.h"

#include "graphics/dialoggamestart.h"

#include <QApplication>



Game::Game(QObject *parent): QObject(parent),
    m_objectManager(std::shared_ptr<ObjectManager>(new ObjectManager)),
                        gameState(std::shared_ptr<GameState>(new GameState())),
                        gameEventHandler(std::shared_ptr<GameEventHandler>(new GameEventHandler))
{

    m_objectManager->setGameEventHandler(gameEventHandler);


    DialogGameStart* gameStartDialog = new DialogGameStart();

    connect(gameStartDialog, &DialogGameStart::accepted, [=](){
        GameStartSettings gameSettings = gameStartDialog->getGameSettings();
        startGame(gameSettings);
    });


    gameStartDialog->show();
    gameStartDialog->raise();
    gameStartDialog->activateWindow();

}

void Game::startGame(const GameStartSettings& gameSettings)
{

    // Init GameEventHandler
     int mapWidth = gameSettings.mapSize.first;
     int mapHeight =  gameSettings.mapSize.second;


    //Make sure MapWindow is created before initializing
    mapWindow = std::shared_ptr<MapWindow>(new MapWindow(nullptr, mapWidth,mapHeight, this->gameEventHandler));



    //CREATE PLAYERS

    for( int i = 0; i < gameSettings.playerCount; ++i)
    {
        std::string nimi = gameSettings.playerNames.at(i);
        std::shared_ptr<Player> player = std::make_shared<Player>(Player(nimi, PlayerColors.at(i), gameEventHandler, {}));
        m_playerList.push_back(player);

    }

    m_objectManager->setPlayers(m_playerList);
    gameState->initGame(std::make_shared<PlayerList>(m_playerList));


    //Create world / gameboard
    Course::WorldGenerator &wg = Course::WorldGenerator::getInstance();
    wg.addConstructor<Course::Forest>(2);
    wg.addConstructor<Course::Grassland>(1);
    wg.addConstructor<Hill>(1);
    wg.addConstructor<Water>(1);
    wg.addConstructor<Swamp>(1);
    wg.addConstructor<Desert>(1);
    wg.generateMap(mapWidth,mapHeight,2,m_objectManager, gameEventHandler);


    for(auto tile : m_objectManager->getTiles())
    {
        mapWindow->drawItem(tile, {CursorInsertMode::TILE, CursorInsertTarget::NONE});
    }

    gameEventHandler->initGameEventHandler(m_objectManager, gameState, mapWindow);


    mapWindow->updatePlayerContext(m_playerList.at(0));
    mapWindow->setGameStateContext(gameState);
    mapWindow->updateProductionContext();
    mapWindow->updateWorkerLabels();
    mapWindow->updateWorkerButtons(gameEventHandler->getCurrentPlayer());
    mapWindow->show();

    gameEventHandler->setGameInitialized(true);


    DialogGameEnd* gameEndDialog = new DialogGameEnd();
    connect(gameEndDialog, &DialogGameEnd::rejected, [=](){
        qApp->exit();
    });
    gameEventHandler->setEndDialog(gameEndDialog);

}

const std::shared_ptr<GameState> &Game::getState()
{
    return this->gameState;
}

PlayerList Game::getPlayers()
{
    return m_playerList;
}

