#ifndef MAPITEM_H
#define MAPITEM_H



#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <memory>
#include "core/gameobject.h"
#include "gamescene.h"
class MapWorkerItem;

/**
 * @brief The MapItem class is an object on the game board.
 */
class MapItem: public QGraphicsItem
{
public:


    /**
     * @brief Constructor for the class.
     *
     * @param obj  gameObject to add TILE object
     * @param size size to set the graphical item in pixels square
     * @param itemType First: type of object, second: tiletype
     * @param parent of the mapItem
     * @post Exception guarantee: No guarantee.
     **/
    MapItem(const std::shared_ptr<Course::GameObject>& obj,
            int size, std::pair<CursorInsertMode, CursorInsertTarget> itemType,
            QGraphicsItem * parent = 0);




public:
    /**
     * @brief boundingRect
     * @return the bounding rectangle of this item.
     */
   QRectF boundingRect() const override;

    /**
     * @brief paints the item
     * @param painter
     * @param option
     * @param widget
     * @note The GraphicsView containing the scene this belongs to
     * usually calls this function.
     */
     void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);


    /**
     * @brief getBoundObject
     * @return the object this item is bound to.
     */
    const std::shared_ptr<Course::GameObject> &getBoundObject();


   std::pair<CursorInsertMode, CursorInsertTarget> getType();


   /**
    * @brief used to add worker graphical item to associate with a tile graphical object
    * @param pointer to workerItem
    */
   void addWorkerMapItem(MapWorkerItem *workerItem);

   /**
    * @brief used for tiles to get how many worker are associated with the tile
    * @return all worker graphical items at the tile
    */
   std::vector<MapWorkerItem *> getTileWorkerItems();

private:

    std::vector<MapWorkerItem *> m_tileWorkers;

protected:

   const std::shared_ptr<Course::GameObject> m_gameobject;
   QPoint m_scenelocation;
   int m_size;
   std::pair<CursorInsertMode, CursorInsertTarget> type;
   static std::map<std::string, QColor> c_mapcolors;
   static void addNewColor(std::string type);
   QPixmap texture;
   QRectF m_boundingRect;
   bool isHovering;
   int m_textureIndex;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
};

#endif // MAPITEM_H
