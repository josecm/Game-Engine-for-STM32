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
#include "menu.h"
#include "level.h"
#include "entity.h"
#include "image.h"
#include "controller.h"


using namespace std;

//enum COLOR { BLACK, WHITE, BLUE , RED, GREEN, YELLOW, ORGANE };
enum SCREEN_BORDER {SCREEN_TOP, SCREEN_BOTTOM, SCREEN_LEFT, SCREEN_RIGHT};
enum GAME_STATE {RUNNING, PAUSED, INITIAL_MENU};
class Level;
class Menu;

class ScreenBorder : public EntitySquare {

    SCREEN_BORDER tipo;

public:
    ScreenBorder(Game *game, SCREEN_BORDER border);

};

class Game : public QGraphicsView
{

private:

    Q_OBJECT

    QGraphicsScene *scene;
    QTimer update_timer;

    vector<Level*> level_list;
    vector<Entity*> entity_list;
    vector<Image*> graphics_list;
    vector<ScreenBorder*> screen_borders;
    Menu* paused_menu;
    Menu* initial_menu;

    COLOR backgroundcolor;
    BitmapImage *background_image;

protected:
    Controller* controller1, *controller2;
    GAME_STATE state;
    bool levelover;
    bool levelsucess;
    int currentlevel;

public:
    Game();


    void addEntity(Entity*);
    void addGraphic(Image *);
    void removeEntity(Entity *);
    void removeGraphic(Image*);
    void clearGraphics();
    bool entityExists(Entity*);
    bool graphicExists(Image*);

    void setMenuPaused(Menu*);
    void setMenuInitial(Menu*);
    void goToInitialMenu();

    void run();
    void stop();
    void pause(bool);

    virtual void collisions();

    void addLevel(Level*);
    void levelupdate();
    void levelOver(bool tf);
    bool isLevelOverSuccess() { return levelsucess; }

    void setBackgroundColor(COLOR clr);
    void setBackgroundImage(BitmapImage *img);
    void removeBackgroundImage();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    GAME_STATE getState() { return state; }

public slots:
    virtual void update();
};




#endif // Game_H
