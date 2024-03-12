#include "mapunititem.h"
#include <QDebug>
#include <QPainter>
#include "player.h"

MapUnitItem::MapUnitItem(const std::shared_ptr<Course::GameObject> &obj, int size, std::pair<CursorInsertMode, CursorInsertTarget> type, QGraphicsItem *parent):
    MapItem(obj, size, type, parent )
{
    //set texture


    if(type.second == CursorInsertTarget::HEADQUARTERS) {
        texture = QPixmap(":/images/sprites/headquarters.png");
        m_size = 48;
    }

    if(type.second == CursorInsertTarget::FARM) {
        texture = QPixmap(":/images/sprites/farm.png");
        m_size = 40;
    }

    if(type.second == CursorInsertTarget::OUTPOST) {
        texture = QPixmap(":/images/sprites/outpost.png");
        m_size = 40;
    }


    if(type.second == CursorInsertTarget::FISHINGHUT) {
        texture = QPixmap(":/images/sprites/fishinghut.png");
        m_size = 40;
    }

    if(type.second == CursorInsertTarget::EMPLOYMENTOFFICE) {
        texture = QPixmap(":/images/sprites/employmentoffice.png");
        m_size = 40;
    }

    if(type.second == CursorInsertTarget::LUMBERMILL) {
        texture = QPixmap(":/images/sprites/lumbermill.png");
        m_size = 40;
    }

    if(type.second == CursorInsertTarget::QUARRY) {
        texture = QPixmap(":/images/sprites/quarry.png");
        m_size = 40;
    }

    if(type.second == CursorInsertTarget::MINE) {
        texture = QPixmap(":/images/sprites/mine.png");
        m_size = 40;
    }

}

QRectF MapUnitItem::boundingRect() const
{

  return QRectF(0,0,m_size,m_size);
}

void MapUnitItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(m_gameobject->getOwner()) {
        //if tileowner is same as the current gamer
        if(std::dynamic_pointer_cast<Player>(m_gameobject->getOwner())->isCurrentTurn(std::dynamic_pointer_cast<Player>(m_gameobject->getOwner()))) {
            painter->drawPixmap(0,0,m_size,m_size, texture);
        }
    }



}
