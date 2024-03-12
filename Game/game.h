#ifndef GAME_H
#define GAME_H

#include "graphics/mapwindow.hh"
#include <memory>
#include "gameeventhandler.h"
#include "gamestate.h"
#include "graphics/dialoggamestart.h"


typedef std::vector<std::shared_ptr<Player>> PlayerList;

const std::vector<QColor> PlayerColors({
    QColor(200,0,0,155),
    QColor(0,200,0,155),
    QColor(200,0,200,155),
    QColor(100,100,0,155),
    QColor(0,100,100,155),
    QColor(100,0,100,155)
});

/**
 * @brief The Game class is the core class of the game.
 */
class Game: public QObject
{

    Q_OBJECT

public:

    Game(QObject *parent = nullptr);

    /**
      * @brief starts the game, initializes multiple things
      * @param GameSettings object, Dialog generates one
      *
      */
    void startGame(const GameStartSettings& gameSettings);

    /**
      * @brief Gets the state of the game
      * @return Current state of the game object
      *
      */
    const std::shared_ptr<GameState> &getState();


    /**
      * @brief Gets list of all the players
      * @return Vector of shared pointers to all players
      *
      */
    PlayerList getPlayers();

private:
    std::shared_ptr<MapWindow> mapWindow;
    std::shared_ptr<ObjectManager> m_objectManager;
    std::shared_ptr<GameState> gameState;
    std::shared_ptr<GameEventHandler> gameEventHandler;

    PlayerList m_playerList;

};

#endif // GAME_H
