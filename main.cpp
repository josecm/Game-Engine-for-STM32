#include <QApplication>
#include <QDebug>
#include "testgame.h"
#include "Vector.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    TestGame *game = new TestGame();
    game->goToInitialMenu();

    game->show();
    return a.exec();

}
