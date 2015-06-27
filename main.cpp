#include <QApplication>
#include <QDebug>
#include "testgame.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestGame *game = new TestGame();
    game->run();
    game->show();

    return a.exec();
}
