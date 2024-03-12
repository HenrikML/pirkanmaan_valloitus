#include "mapitem.h"
#include <QPen>
#include <QPainter>
#include <QDebug>
#include "player.h"
#include "gameeventhandler.h"
#include <random>

#include "core/coordinate.h"
std::map<std::string, QColor> MapItem::c_mapcolors = {};

MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj, int size, std::pair<CursorInsertMode, CursorInsertTarget> itemType, QGraphicsItem * parent): QGraphicsItem(parent),
     m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()), m_size(size), type(itemType)
{
    setAcceptHoverEvents(true);
    m_size = 64;
    setPos(m_scenelocation.x()*m_size,m_scenelocation.y()*m_size);
    isHovering = false;
}

void MapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    isHovering = true;


    if(getBoundObject()->getOwner()) {
     qDebug() << getBoundObject()->getOwner()->getName().c_str();
    }
    else {
         qDebug() << "Tilellä ei omistajaa";
    }

    QGraphicsItem::hoverEnterEvent(event);
    update();
}

void MapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    isHovering = false;
    update();
}

void MapItem::addWorkerMapItem(MapWorkerItem *workerItem)
{
    m_tileWorkers.push_back(workerItem);
}

std::vector<MapWorkerItem *> MapItem::getTileWorkerItems() {
    return m_tileWorkers;
}



QRectF MapItem::boundingRect() const
{
    qreal topOffset = 10;
    return QRectF(0,topOffset,m_size,m_size);
}



void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );

    double hoverFactor = 0.7;

    QColor brushColor = Qt::red;
    QColor penColor = Qt::black;
    QPixmap pixmapTexture;

    std::shared_ptr<Player> tileOwner = std::dynamic_pointer_cast<Player>(getBoundObject()->getOwner());


    if (m_gameobject->getType() == "Forest") {
        brushColor = Qt::green;
        pixmapTexture = QPixmap(":/images/sprites/forest2.png");

    }

    if (m_gameobject->getType() == "Desert") {
          brushColor = Qt::yellow;
          pixmapTexture = QPixmap(":/images/sprites/desert.png");

    }

    if (m_gameobject->getType() == "Grassland") {
          brushColor = Qt::yellow;
          pixmapTexture = QPixmap(":/images/sprites/grassland.png");

    }

    if (m_gameobject->getType() == "Hill") {
          brushColor = Qt::yellow;
          pixmapTexture = QPixmap(":/images/sprites/hill2.png");

    }

    if (m_gameobject->getType() == "Swamp") {
          brushColor = Qt::yellow;
          pixmapTexture = QPixmap(":/images/sprites/swamp2.png");

    }

    if (m_gameobject->getType() == "Water") {
          brushColor = Qt::yellow;



            pixmapTexture = QPixmap(":/images/sprites/water2.png");


    }

    if (m_gameobject->getType() == "Grassland") {
            brushColor = QColor(50,150,50);
    }

    if (m_gameobject->getType() == "Swamp") {
          brushColor = QColor(80,150,90);
    }

    if (m_gameobject->getType() == "Water") {
      brushColor = QColor(50,150,250);
    }

    if (m_gameobject->getType() == "Hill") {
          brushColor = QColor(100,110,100);
    }


    QRectF border = boundingRect();


     painter->drawPixmap(0,+10,pixmapTexture);
     painter->setPen(QPen(QColor(Qt::darkGray)));
     painter->drawRect(border);

    if(m_gameobject->getOwner()) {
        //if tileowner is same as the current gamer
        if(!std::dynamic_pointer_cast<Player>(m_gameobject->getOwner())->isCurrentTurn(tileOwner)) {

            QColor overlayColor(tileOwner->getPlayerColor());
            painter->fillRect(border, QBrush(QColor(overlayColor.red()*0.2, overlayColor.green()*0.2, overlayColor.blue()*0.2, 245)));


        }
    } else {
        painter->fillRect(border, QBrush(QColor(40,40,40,200)));
    }

    if(isHovering) {
       QBrush  brush;
       QColor yellow = Qt::yellow;
       brush.setColor(yellow);
       painter->setBrush(QBrush(brush));

       //hover highlight
       painter->fillRect(border, QBrush(QColor(200, 128, 255, 94)));

       painter->drawRect(border);
    }

    //Neliö joka on varsinainen "tile"


}

const std::shared_ptr<Course::GameObject> &MapItem::getBoundObject()
{
    return m_gameobject;
}



std::pair<CursorInsertMode, CursorInsertTarget> MapItem::getType()
{
    return type;
}



void MapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

}

void MapItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}


