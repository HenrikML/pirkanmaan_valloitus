#ifndef PLAYER_H
#define PLAYER_H

#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/gameobject.h"
#include <QColor>

#include "core/resourcemaps.h"
#include "workers/workerbase.h"

class GameEventHandler;


typedef std::map<Course::BasicResource, int> PlayerResource;
const int INITIAL_WORKER_LIMIT = 5;

/**
 * @brief The Player class stores a player's information.
 */
class Player: public Course::PlayerBase
{
public:
    Player(const std::string& name,
           QColor color,
           const std::shared_ptr<GameEventHandler>& ghandler,
           const std::vector<std::shared_ptr<Course::GameObject>> objects = {});

    PlayerResource &getResources();
    QColor getPlayerColor();
    bool hasEnoughResourcesToBuild(Course::ResourceMap target);

    bool isCurrentTurn(const std::shared_ptr<Player> &player);

    void setWorkerLimit(const int &count);
    void modifyWorkerLimit(const int &count);
    int getWorkerLimit();


private:
    PlayerResource m_playerResources;
    QColor playerColor;
    int m_workerLimit;
    std::weak_ptr<GameEventHandler> m_ghandler;

};

#endif // PLAYER_H
