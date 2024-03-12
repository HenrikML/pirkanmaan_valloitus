#include "player.h"
#include "core/gameobject.h"
#include <QDebug>
#include "core/playerbase.h"
#include "gameeventhandler.h"
#include "core/resourcemaps.h"



Player::Player(const std::string& name,
               QColor color,
               const std::shared_ptr<GameEventHandler>& ghandler,
               const std::vector<std::shared_ptr<Course::GameObject>> objects):
               Course::PlayerBase(name),
               playerColor(color),
               m_ghandler(ghandler)
{

    m_workerLimit = INITIAL_WORKER_LIMIT;

    //set Initial resources
    m_playerResources = {
        {Course::BasicResource::MONEY, 2000},
        {Course::BasicResource::STONE, 1250},
        {Course::BasicResource::ORE, 500},
        {Course::BasicResource::WOOD, 500},
        {Course::BasicResource::FOOD, 2000},
    };

}

PlayerResource& Player::getResources()
{
    return m_playerResources;
}

QColor Player::getPlayerColor()
{
    return playerColor;
}

bool Player::hasEnoughResourcesToBuild(Course::ResourceMap target)
{
    bool isEnough = true;

    int moneyReq = 0;
    int stoneReq = 0;
    int oreReq = 0;
    int woodReq = 0;
    int foodReq = 0;

    if( target.find(Course::BasicResource::MONEY) != target.end() ) {
        moneyReq = target.at(Course::BasicResource::MONEY);
        if(moneyReq > target.at(Course::BasicResource::MONEY))
                isEnough = false;
    }

    if( target.find(Course::BasicResource::WOOD) != target.end() ) {
        stoneReq = target.at(Course::BasicResource::WOOD);
           if(stoneReq > m_playerResources.at(Course::BasicResource::WOOD))
               isEnough = false;
    }

    if( target.find(Course::BasicResource::ORE) != target.end() ) {
        oreReq = target.at(Course::BasicResource::ORE);
            if(oreReq > m_playerResources.at(Course::BasicResource::ORE))
                isEnough = false;
    }

    if( target.find(Course::BasicResource::STONE) != target.end() ) {
        woodReq = target.at(Course::BasicResource::STONE);
            if(woodReq > m_playerResources.at(Course::BasicResource::STONE))
                isEnough = false;
    }

    if( target.find(Course::BasicResource::FOOD) != target.end() ) {
        foodReq = target.at(Course::BasicResource::FOOD);
            if(foodReq > m_playerResources.at(Course::BasicResource::FOOD))
                isEnough = false;
    }

    qDebug() << "Requirements: " << moneyReq << " : " << stoneReq << " : " << oreReq << ": " << woodReq << " : " << foodReq;




    return isEnough;
}

bool Player::isCurrentTurn(const std::shared_ptr<Player> &player)
{


    if(player == m_ghandler.lock()->getCurrentPlayer()) {
        return true;
    }
    else
    {
        return false;
    }


}

void Player::setWorkerLimit(const int &count)
{
    m_workerLimit = count;
}

void Player::modifyWorkerLimit(const int &count)
{
    m_workerLimit += count;
    //Clamp to zero
    if(m_workerLimit < 0) {
        m_workerLimit = 0;
    }
}

int Player::getWorkerLimit()
{
    return m_workerLimit;
}


