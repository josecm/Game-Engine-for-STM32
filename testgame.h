#ifndef TESTGAME_H
#define TESTGAME_H

#include <QDir>
#include <QDebug>
#include <limits>
#include "gameview.h"
#include "menu.h"
#include <sstream>


class Player : public EntityCircle {


public:
    Player(Game* game, int x, int y);
    virtual void onCollision(Entity &ent, Vector *mtd);
    virtual void readInput();
};

class Wall : public EntitySquare {

public:
    Wall(Game* game, int x = 0, int y = 0, int height = 1, int width = 1,  string wallpic = ":/imagens/transparent.png");

};

class WallBig : public Wall {

public:
    WallBig(Game* game, int x = 0, int y = 0);

};

class WallMedium : public Wall {

public:
    WallMedium(Game *game, int x= 0, int y = 0);

};


class WallSmall : public Wall {

public:
    WallSmall(Game *game, int x= 0, int y = 0);

};



class TestGame : public Game
{

    friend class Player;
    friend class TestLevel;

    Player *player;
    EntitySquare *finish;
    TextBoxImage *message, *message2, *menu;
    SquareImage *sqr;
    int counter;

public:
    TestGame();

};

class TestLevel : public Level {

    int px, py, fx, fy;

public:

    TestLevel(Game* game, int px, int py, int fx, int fy) : Level(game), px(px), py(py), fx(fx), fy(fy) { }

    virtual void initialize();
    virtual void finalize();

};

#endif // TESTGAME_H
