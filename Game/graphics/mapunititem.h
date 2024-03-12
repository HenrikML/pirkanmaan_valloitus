#ifndef MAPUNITITEM_H
#define MAPUNITITEM_H

#include "graphics/mapitem.h"

class MapUnitItem: public MapItem
{
public:

    /**
     * @brief Constructor for the class.
     *
     * @param obj  gameObject to add BUILDING object
     * @param size size to set the graphical item in pixels square
     * @param itemType First: type of object, second: tiletype
     * @param parent of the mapItem
     * @post Exception guarantee: No guarantee.
     **/
    MapUnitItem(const std::shared_ptr<Course::GameObject> &obj,
                int size, std::pair<CursorInsertMode,CursorInsertTarget> type,
                QGraphicsItem * parent = 0);


    QRectF boundingRect() const override;


    void paint(QPainter *painter,
              const QStyleOptionGraphicsItem *option,
              QWidget *widget) override;


};

#endif // MAPUNITITEM_H
