#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "core/playerbase.h"
#include "player.h"

/**
 * @brief The GameState class keeps track of the current game state.
 */
class GameState
{
public:
    GameState();
    bool endTurn();
    bool initGame(const std::shared_ptr<std::vector<std::shared_ptr<Player>>> &players);
    std::weak_ptr<Player> getCurrentPlayer();

    std::weak_ptr<Player> currentPlayer;
    std::shared_ptr<std::vector<std::shared_ptr<Player>>> getPlayers();
    unsigned int getTurncount();
private:

    unsigned int currentPlayerIndex;
    unsigned int playerCount;
    unsigned int turnCount;
    //TODO: Jos ongelmia playereitten kanssa, tämä oli alunperin weak_ptr ?? mutta ei toiminut
    std::shared_ptr<std::vector<std::shared_ptr<Player>>> m_players;

};

#endif // GAMESTATE_H
