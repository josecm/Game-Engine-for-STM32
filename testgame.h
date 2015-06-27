#ifndef TESTGAME_H
#define TESTGAME_H

#include <QDir>
#include <QDebug>
#include <limits>
#include "gameview.h"
#include <sstream>


class Player : public EntityCircle {


public:
    Player(Game* game, int x, int y);
    virtual void onCollision(Entity &ent, Vector *mtd);
    virtual void readInput();
};

class Wall : public EntitySquare{


public:
    Wall(Game* game, int x = 0, int y = 0);

};



class TestGame : public Game
{

    friend class Player;
    friend class TestLevel;

    Player *player;
    EntitySquare *finish;
    TextBoxImage *message, *message2;
    int counter;

public:
    TestGame();

};

class TestLevel : public Level {

    int px, py, fx, fy;

public:

    TestLevel(Game* game, int px, int py, int fx, int fy) : Level(game), px(px), py(py), fx(fx), fy(fy) { }

    virtual void initialize() {

        static TestGame *testgame = dynamic_cast<TestGame*>(game);

        testgame->player->setPosition(px,py);
        testgame->player->setVelocity(0.0, 0.0);
        testgame->finish->setPosition(fx,fy);


        if(game->isLevelOverSuccess()){
            (testgame->counter)++;
            ostringstream stream;
            stream << testgame->counter;
            testgame->message->setText(stream.str());
         }

    }

};

#endif // TESTGAME_H
