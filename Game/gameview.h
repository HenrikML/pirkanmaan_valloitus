#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <memory>
#include "graphics/gamescene.h"
#include "graphics/mapwindow.hh"


class GameView : public QGraphicsView
{
public:
    GameView(QWidget *parent);

    std::weak_ptr<CursorMode> cursorMode;
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

    // QObject interface
public:


    // QObject interface
public:
    bool event(QEvent *event);

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // GAMEVIEW_H
