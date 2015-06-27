#ifndef Game_H
#define Game_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QElapsedTimer>

////////
#include <vector>
#include <limits>
#include "entity.h"
#include "image.h"
#include "controller.h"


using namespace std;
class Entity;

enum SCREEN_BORDERS {SCREEN_TOP, SCREEN_BOTTOM, SCREEN_LEFT, SCREEN_RIGHT};

class Game : public QGraphicsView
{

private:

    Q_OBJECT

    QGraphicsScene *scene;
    QTimer update_timer;
    vector<Entity*> entity_list;
    //vector<Entity*> fixed_entity_list;
    vector<Entity*> screen_borders;

    Entity *focused;

protected:
    Controller* controller1, *controller2;
    bool game_over;
public:
    Game();

    //IDEIAS PARA FUNÇOES
    //virtual void initialize();
    void addEntity(Entity*);
    //void addFixedEntity();
    void addGraphic(Image *);
    void clearGraphics();
    void run();
    void stop();
    //void pause();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


public slots:
    virtual void update();
};

#endif // Game_H
