#include "gamestate.h"
#include <QDebug>
GameState::GameState()
{

}

bool GameState::endTurn()
{
    turnCount++;
    unsigned int playerIndex = turnCount % playerCount;
    qDebug() << "Player index: " << playerIndex;
    currentPlayer = m_players->at(playerIndex);
    return true;
}

bool GameState::initGame(const std::shared_ptr<std::vector<std::shared_ptr<Player>>> &players)
{
    playerCount = unsigned(players->size());
    m_players = players;
    currentPlayer = players->at(0);
    turnCount = 0;
    return true;
}

 std::weak_ptr<Player>GameState::getCurrentPlayer()
{
     return currentPlayer;
 }

 std::shared_ptr<std::vector<std::shared_ptr<Player> > > GameState::getPlayers()
 {
     return m_players;
 }

 unsigned int GameState::getTurncount()
 {
     return turnCount;
 }
