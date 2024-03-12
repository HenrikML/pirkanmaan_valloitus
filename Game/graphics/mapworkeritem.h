#ifndef MAPWORKERITEM_H
#define MAPWORKERITEM_H

#include "core/objectmanager.hh"
#include "graphics/mapitem.h"

class MapWorkerItem : public MapItem
{
public:
    /**
     * @brief Constructor for the class.
     *
     * @param obj  gameObject to add WORKER object
     * @param size size to set the graphical item in pixels square
     * @param itemType First: type of object, second: tiletype
     * @param parent of the mapItem
     * @post Exception guarantee: No guarantee.
     **/
    MapWorkerItem(const std::shared_ptr<Course::GameObject> &obj,
                  int size, std::pair<CursorInsertMode, CursorInsertTarget>
                  type,
                  QGraphicsItem * parent = 0);


private:
    /**
     * @brief getBoundObject
     * @return the object this item is bound to.
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
              QWidget *widget) override;

    std::weak_ptr<ObjectManager> m_objectManager;


    // QGraphicsItem interface
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    bool m_isHovered = false;
};

#endif // MAPWORKERITEM_H
