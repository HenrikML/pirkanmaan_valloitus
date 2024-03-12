#include "gameview.h"
#include "graphics/gamescene.h"
GameView::GameView(QWidget *parent): QGraphicsView(parent)
{

}

void GameView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "view mouse press";
    QGraphicsView::mousePressEvent(event);
}


bool GameView::event(QEvent *event)
{
    QGraphicsView::event(event);
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}
