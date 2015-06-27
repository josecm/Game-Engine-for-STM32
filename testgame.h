#ifndef TESTGAME_H
#define TESTGAME_H

#include <limits>
#include "gameview.h"
#include "entity.h"
#include "image.h"
#include <sstream>


class Player : public EntityCircle {


public:
    Player(Game* game, int x, int y);
    virtual void onCollision(Entity &ent, Vector *mtd);
    virtual void update();
};

class Wall : public EntitySquare{


public:
    Wall(Game* game, int x = 0, int y = 0);

};

class TestGame : public Game
{

    friend class Player;

    Player *player;
    EntitySquare *finish;
    TextBoxImage *message, *message2;
    int counter;

public:
    TestGame();

};

#endif // TESTGAME_H
