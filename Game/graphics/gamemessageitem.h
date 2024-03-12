#ifndef GAMEMESSAGEITEM_H
#define GAMEMESSAGEITEM_H


#include "QGraphicsItem"

/**
 * @brief The GameMessageItem class displays notifications to players.
 */
class GameMessageItem: public QGraphicsSimpleTextItem
{
public:
    /**
     * @brief Constructor for the class.
     * @param text that points to the student's GameEventHandler.
     * @post Exception guarantee: No guarantee.
     **/

    GameMessageItem(std::string text,  QGraphicsItem * parent = 0);
};

#endif // GAMEMESSAGEITEM_H
