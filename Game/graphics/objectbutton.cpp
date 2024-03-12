#include "objectbutton.h"
#include <QDebug>

ObjectButton::ObjectButton(const QString &text, QWidget *parent):
    QPushButton(text, parent)
{

}

bool ObjectButton::event(QEvent *event)
{

    switch (event->type()) {
    case QEvent::HoverEnter:
        emit hoverEnter();
        break;
    case QEvent::HoverLeave:
        emit hoverLeave();
        break;
    }
    QPushButton::event(event);
    return true;
}
