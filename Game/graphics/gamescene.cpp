#include "gamescene.h"
#include "QGraphicsItem"
#include "mapitem.h"
#include <math.h>
#include <QDebug>
#include "mapwindow.hh"
#include <QGraphicsSceneEvent>
#include "gameeventhandler.h"
#include "graphics/mapunititem.h"
#include "tiles/tilebase.h"
#include "gamemessageitem.h"
#include "mapworkeritem.h"

GameScene::GameScene(QWidget *qt_parent, int width, int height, int scale, const std::shared_ptr<GameEventHandler>& ghandler):
                      QGraphicsScene(qt_parent),m_mapBoundRect(nullptr),
                      m_width(width), m_height(height), m_scale(50),
                      m_gameEventHandler(ghandler)
{

}


void GameScene::drawItem( std::shared_ptr<Course::GameObject> obj, std::pair<CursorInsertMode, CursorInsertTarget> type, MapItem* parentTile )
{
    if(type.first == CursorInsertMode::TILE) {
          MapItem* nItem = new MapItem(obj, m_scale, type);
            addItem(nItem);
    }

    if(type.first == CursorInsertMode::BUILDING) {
        qDebug() << " piirretään  bnuilding";
        MapUnitItem* nItem = new MapUnitItem(obj,m_scale,type);
        addItem(nItem);
    }

    if(type.first ==  CursorInsertMode::WORKER) {
        qDebug() << "Piirretään worker";
        MapWorkerItem* nItem = new MapWorkerItem(obj,m_scale, type);
        parentTile->addWorkerMapItem(nItem);


        //get how many workers are in the tile and add position based on that
        unsigned workersOnTile = parentTile->getTileWorkerItems().size() % 4 - 1;
        int offSetX = 20*workersOnTile;
        int offSetY = 0;
        if(workersOnTile > 3) { offSetY = 20; }
        int hardOffsetY = 50;

        nItem->setPos(parentTile->pos().x()+offSetX, parentTile->pos().y()+hardOffsetY + offSetY );
        addItem(nItem);

    }
}


void GameScene::handleBuildEvent(QPointF point)
{

    MapItem *target = qgraphicsitem_cast<MapItem*>(itemAt(point, QTransform()));
    std::string gameMessage;

    //CHECKAA ONKO TILE VAI JOKU GAMEOBJECT
    std::shared_ptr<Course::GameObject> boundObject = target->getBoundObject();

    qDebug()<< "bound type:" << boundObject->getType().c_str();

    if(target->getType().first == CursorInsertMode::TILE) {


    Course::ObjectId itemId = m_gameEventHandler.lock()->constructBuilding(
                                m_gameEventHandler.lock(),
                                m_gameEventHandler.lock()->getCurrentPlayer(),
                                currentBuildTarget,
                                std::dynamic_pointer_cast<Course::TileBase>(
                                                       target->getBoundObject()),
                                  gameMessage);

    if(itemId != 0 && itemId != NULL)
    {
        std::shared_ptr<Course::BuildingBase> building = m_gameEventHandler.lock()->objectManager.lock()
                ->getPlayerBuildingById(
                    m_gameEventHandler.lock()->getCurrentPlayer(),
                    itemId
                    );

        //Draw item to GUI

        drawItem(std::dynamic_pointer_cast<Course::GameObject>(building),
                 {CursorInsertMode::BUILDING, currentBuildTarget});

        currentBuildTarget = CursorInsertTarget::NONE;
        m_gameEventHandler.lock()->resetCursorMode();

        }
      else
        {
            m_gameEventHandler.lock()->setGameEventMessage(gameMessage );
        }
    }
}


void GameScene::insertWorkerToTile(QPointF point)
{
    qDebug() << "insertataan workjeria tilelle";

    try {
        MapItem *targetTileItem = qgraphicsitem_cast<MapItem*>(itemAt(point, QTransform()));
        if(targetTileItem)
        {
            std::string gameMessage;
            qDebug() << "saatiin target tilen mapitem";
            std::shared_ptr<Course::GameObject> tileBoundGameObject = targetTileItem->getBoundObject();
            if(tileBoundGameObject != nullptr && targetTileItem->getType().first == CursorInsertMode::TILE)

            {

                std::shared_ptr<Course::TileBase> boundTile = std::dynamic_pointer_cast<Course::TileBase>(tileBoundGameObject);


                qDebug() << "current gamer: " << m_gameEventHandler.lock()->getCurrentPlayer()->getName().c_str();
                const std::shared_ptr<Course::iGameEventHandler>& ghandlerPtr = std::dynamic_pointer_cast<Course::iGameEventHandler>(m_gameEventHandler.lock());

                bool success =  m_gameEventHandler.lock()->insertWorkerToTileForPlayer(boundTile,
                                                                        targetTileItem,
                                                                        m_gameEventHandler.lock()->getCurrentPlayer(),
                                                                        currentBuildTarget,
                                                                        ghandlerPtr,
                                                                        gameMessage
                                                               );
                if(success)
                {
                //Piirretään worker GUI:hin
                    qDebug() << "RESEOITADAN KURSOR";
                   m_gameEventHandler.lock()->resetCursorMode();

                }

                else
                {
                 m_gameEventHandler.lock()->setGameEventMessage(gameMessage );
                }
            }
        }


    }
    catch(...) {
        qDebug() << "clickas muualle ja kaatu kun koitettii laittaa worker";
    }
}



void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

        if ( sceneRect().contains(event->scenePos()))
        {
            //Insert Building
            if(currentCursorMode == CursorMode::Build && event->button() == Qt::MouseButton::LeftButton) {
                QPointF point = event->scenePos();
                handleBuildEvent(point);
            }
            //Insert worker
            if(currentCursorMode == CursorMode::SetWorker && event->button() == Qt::MouseButton::LeftButton) {
              QPointF point = event->scenePos();
              insertWorkerToTile(point);
            }
        }

    QGraphicsScene::mousePressEvent(event);

}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}




