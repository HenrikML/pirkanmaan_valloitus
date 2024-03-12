#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include "graphics/simplegamescene.h"
#include <QGraphicsPixmapItem>
#include "gamemessageitem.h"



class MapItem;
class GameEventHandler;


const std::pair<int, int> SCENE_WIDTH_LIMITS = {1, 100};
const std::pair<int, int> SCENE_HEIGHT_LIMITS = {1, 100};
const std::pair<int, int> SCENE_SCALE_LIMITS = {1, 500};

enum CursorMode {
    Normal,
    Select,
    Build,
    SetWorker
};

enum CursorInsertTarget {
    NONE,
    FARM,
    OUTPOST,
    MINE,
    HEADQUARTERS,
    FISHINGHUT,
    MINER,
    FARMER,
    STONEMASON,
    LUMBERJACK,
    FISHER,
    EMPLOYMENTOFFICE,
    LUMBERMILL,
    QUARRY
};




enum CursorInsertMode {
    TILE,
    WORKER,
    BUILDING,
};

/**
 * @brief The GameScene class handles the game board.
 */
class GameScene: public QGraphicsScene
{
public:

    /**
     * @brief Constructor for the class.
     *
     * @param qt_parent  QWidget parent
     * @param width map width
     * @param height map height
     * @param scale of the map, UNUSED
     * @param ghandler pointer to gameHandler
     * @post Exception guarantee: No guarantee.
     **/
    GameScene(QWidget* qt_parent,
              int width,
              int height,
              int scale,
              const std::shared_ptr<GameEventHandler>& ghandler);


    /**
     * @brief draw a new item to the map.
     * @param obj shared ptr to valid gameObject object
     * @param type map with first as: what type item to drwa, second as: target to draw
     * @post Exception guarantee: None
     */
    void drawItem(std::shared_ptr<Course::GameObject> obj,
                  std::pair<CursorInsertMode, CursorInsertTarget> type,
                  MapItem* parentTile = nullptr);

    CursorMode currentCursorMode = CursorMode::Normal;
    CursorInsertTarget currentBuildTarget = CursorInsertTarget::NONE;


private:
    QGraphicsItem* m_mapBoundRect;
    int m_width;
    int m_height;
    int m_scale;
    std::weak_ptr<GameEventHandler> m_gameEventHandler;


    void handleBuildEvent(QPointF point);
    void insertWorkerToTile(QPointF point);

protected:
    //Qt overriden  scene mousePressEvents
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // GAMESCENE_H
