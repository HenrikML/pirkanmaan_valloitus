#include <QApplication>
#include "graphics/dialoggamestart.h"
#include "game.h"

int main(int argc, char* argv[])
{
    int result = 0;
    QApplication app(argc, argv);
    Game game;
    return app.exec();

}
