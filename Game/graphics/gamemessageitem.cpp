#include "gamemessageitem.h"


GameMessageItem::GameMessageItem(std::string text, QGraphicsItem *parent)
{
   setText(QString(text.c_str()));
}
