#include "graphics/mapworkeritem.h"
#include "graphics/mapitem.h"


#include <QDebug>
#include <QPainter>
#include "player.h"
#include "tiles/tilebase.h"

MapWorkerItem::MapWorkerItem(const std::shared_ptr<Course::GameObject> &obj,
                             int size,
                             std::pair<CursorInsertMode, CursorInsertTarget> type,
                             QGraphicsItem *parent):
                             MapItem(obj, size, type, parent )
{


     m_size = 20;
    switch(type.second) {
        case(CursorInsertTarget::MINER):
            texture = QPixmap(":/images/sprites/miner.png");
        break;

        case(CursorInsertTarget::FARMER):
         texture = QPixmap(":/images/sprites/farmer.png");
        break;

        case(CursorInsertTarget::STONEMASON):
            texture = QPixmap(":/images/sprites/stonemason.png");
        break;

        case(CursorInsertTarget::LUMBERJACK):
            texture = QPixmap(":/images/sprites/lumberjack.png");
        break;

        case(CursorInsertTarget::FISHER):
            texture = QPixmap(":/images/sprites/fisher.png");
        break;

        default:
            texture = QPixmap(":/images/sprites/worker.png");
        break;
    }


}

QRectF MapWorkerItem::boundingRect() const
{

  return QRectF(0,0,m_size,m_size);
}

void MapWorkerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    if(m_gameobject->getOwner()) {
        //if tileowner is same as the current gamer
        if(std::dynamic_pointer_cast<Player>(m_gameobject->getOwner())->isCurrentTurn(std::dynamic_pointer_cast<Player>(m_gameobject->getOwner()))) {

            if(m_isHovered) {
                  setScale(1.2);
                  painter->drawPixmap(0,0,m_size,m_size, texture);

            } else {
                setScale(1.0);
                painter->drawPixmap(0,0,m_size,m_size, texture);
            }
        }
    }
}

void MapWorkerItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_isHovered = true;
    update();
}

void MapWorkerItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_isHovered = false;
    update();
}
