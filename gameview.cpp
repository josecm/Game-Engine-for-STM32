#include "gameview.h"

ScreenBorder::ScreenBorder(Game *game, SCREEN_BORDER border) : EntitySquare(game){

    tipo = border;

    if(border == SCREEN_TOP){
        setHeight(2);
        setWidth(800);
        setPosition(0, -10);
        setMass(std::numeric_limits<float>::max());
    } else if(border == SCREEN_BOTTOM){
        setHeight(2);
        setWidth(800);
        setPosition(0, 600);
        setMass(std::numeric_limits<float>::max());
    } else if(border == SCREEN_LEFT){
        setHeight(600);
        setWidth(2);
        setPosition(-10, 0);
        setMass(std::numeric_limits<float>::max());
    } else if(border == SCREEN_RIGHT){
        setHeight(600);
        setWidth(2);
        setPosition(800, 0);
        setMass(std::numeric_limits<float>::max());
    }

}

Game::Game() : QGraphicsView(), scene(new QGraphicsScene)
{


    levelover = false; levelsucess = false;
    currentlevel = 0;
    state = RUNNING;
    controller1 = new Controller();
    controller2 = new Controller();
    paused_menu = NULL;

    ScreenBorder *border;
    border = new ScreenBorder(this, SCREEN_TOP); screen_borders.push_back(border);
    border = new ScreenBorder(this, SCREEN_BOTTOM); screen_borders.push_back(border);
    border = new ScreenBorder(this, SCREEN_RIGHT); screen_borders.push_back(border);
    border = new ScreenBorder(this, SCREEN_LEFT); screen_borders.push_back(border);

    for(Entity* fig : screen_borders)
        entity_list.push_back(fig);

    //CENAS DO QT

    setFocus();
    scene->setSceneRect(0, 0, 800, 600);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(800, 600);
    this->setScene(scene);

    update_timer.setInterval(17);
    connect(&update_timer, SIGNAL(timeout()), this, SLOT(update()) );
    update_timer.start();
}

void Game::run(){
    level_list[currentlevel]->startlevel();
    state = RUNNING;
}

void Game::pause(bool tf){

    if(paused_menu == NULL)
        return;

    if(tf){
        if(state == PAUSED)
            return;

        state = PAUSED;
        paused_menu->startMenu();

    } else {

        if(state != PAUSED)
            return;

        state = RUNNING;
        paused_menu->endMenu();

    }
}

void Game::stop(){
    update_timer.stop();
}

void Game::addLevel(Level *lvl){
    level_list.push_back(lvl);
}

void Game::addEntity(Entity* ent){

    entity_list.push_back(ent);
    graphics_list.push_back(ent);

    scene->addItem(ent->getQitem());
}

void Game::addGraphic(Image *img){

    graphics_list.push_back(img);

    scene->addItem(img->getQitem());
}

void Game::removeEntity(Entity *ent){

    for(int i = 0; i < entity_list.size(); i++){
        if(ent == entity_list[i]){
            scene->removeItem(entity_list[i]->getQitem());
            entity_list.erase(entity_list.begin() + i);
            return;
        }
    }

}

void Game::removeGraphic(Image* ent){

    for(int i = 0; i < graphics_list.size(); i++){
        if(ent == graphics_list[i]){
            scene->removeItem(graphics_list[i]->getQitem());
            graphics_list.erase(graphics_list.begin() + i);
            return;
        }
    }
}

void Game::clearGraphics(){
    scene->clear();
}

void Game::setMenuPaused(Menu *menu){
    paused_menu = menu;
}

void Game::levelOver(bool tf){
    levelover = true;
    levelsucess = tf;
}

void Game::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left)
        controller1->left = 1;
    else if(event->key() == Qt::Key_Right)
        controller1->right = 1;
    else if(event->key() == Qt::Key_Up)
        controller1->up = 1;
    else if(event->key() == Qt::Key_Down)
        controller1->down = 1;
    else if(event->key() == Qt::Key_Space)
        controller1->space = 1;
    else if(event->key() == Qt::Key_P)
        controller1->p_button = 1;

}

void Game::keyReleaseEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left)
        controller1->left = 0;
    else if(event->key() == Qt::Key_Right)
        controller1->right = 0;
    else if(event->key() == Qt::Key_Up)
        controller1->up = 0;
    else if(event->key() == Qt::Key_Down)
        controller1->down = 0;
    else if(event->key() == Qt::Key_Space)
        controller1->space = 0;
    else if(event->key() == Qt::Key_P)
        controller1->p_button = 0;

}

void Game::collisions(){

    Vector normal;

    for(int i = 0; i < entity_list.size(); i++){
        for(int k = 0; k < entity_list.size(); k++){

            if(entity_list[k]->isFixed() && entity_list[i]->isFixed())
                continue;

            if(k == i)
                continue;

            if(entity_list[i]->collidesWith(entity_list[k], &normal)){
                entity_list[i]->onCollision(*(entity_list[k]), &normal);
            }

        }
    }

}

void Game::update(){

    if(state == RUNNING){

        collisions();

        for(Entity *ent : entity_list)
            ent->readInput();

        for(Entity *ent : entity_list)
            ent->update();

        if(levelover){
            levelover = false;
            if(levelsucess){
                level_list[currentlevel]->endlevel();
                if(++currentlevel == level_list.size())
                    currentlevel = 0;
                level_list[currentlevel]->startlevel();
            } else {
                level_list[currentlevel]->initialize();
            }
        }

    }

    if(state == PAUSED) {
        paused_menu->readInput();

    }

}

