#ifndef ENTITY_H
#define ENTITY_H
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QDebug>
#include <QWidget>

//////
#include <typeinfo>
#include "gameview.h"
#include "vector.h"
#include "image.h"
#include "controller.h"

using namespace std;

class Game;
class Entity;
class EntitySquare;
class EntityCircle;

enum COLLISION_TYPE {CIRCLE, SQUARE} ;

class Entity : public BitmapImage
{   

    //friend class GameView;

protected:

    Game *game;
    Controller *input;
    Vector velocity;
    Vector deltaV;
    float mass;
    float damping;
    float friction;
    bool active;
    COLLISION_TYPE col_type;

public:
    Entity(Game *game, int x = 0, int y = 0, int heigth = 1, int width = 1, float angle = 0.0, string bitmap = "/Users/Ze/Desktop/finishline.png");
    virtual void update();
    bool collidesWith(Entity *, Vector *normal);
    virtual bool collideSquare(EntitySquare*, Vector *normal) = 0;
    virtual bool collideCircle(EntityCircle*, Vector *normal) = 0;
    virtual void onCollision(Entity &ent, Vector *mtd);
    virtual void bounce(Entity &ent, Vector *normal);

    void setInput(Controller *input) { this->input = input; }

    void setVelocity(float x, float y);
    Vector getVelocity() { return velocity; }
    void setMass(float mass);
    float getMass() { return mass; }
    void setDamping(float damp);
    float getDamping();
    void setFriction(float fric);
    float getFriction();
    void setActive(bool val) { active = val; }
    bool isActive(){ return active; }

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

class EntitySquare : public Entity {

    friend class EntityCircle;

    bool rotatedBoxReady;
    Vector corners[4];
    float edge01Min, edge01Max;
    float edge03Min, edge03Max;
    Vector edge01, edge03;


    bool collideCornerCircle(EntityCircle*, Vector&);
    bool collideSquare(EntitySquare*, Vector *normal);
    bool collideCircle(EntityCircle*, Vector *normal);
    void computeRotatedBox();
    bool projectionOverlap(EntitySquare *ent, Vector *normal);

public:

    EntitySquare(Game *game, int x = 0, int y = 0, int heigth = 100, int width = 100, float angle = 0.0, string bitmap = "/Users/Ze/Desktop/rass100.bmp");
    void update();
    bool collidesWith(Entity *);

};

class EntityCircle : public Entity {

    friend class EntitySquare;

    int radius;
    bool collideSquare(EntitySquare*, Vector *normal);
    bool collideCircle(EntityCircle*, Vector *normal);

public:

    EntityCircle(Game *game, int x = 0, int y = 0, int radius = 50, string bitmap = "/Users/Ze/Desktop/circle100.png");
    bool collidesWith(Entity *);
    void update();

    void setRadius(int rad) { radius = rad; }
    int getRadius() { return radius; }

};

#endif // ENTITY_H
