#include "gameview.h"

Game::Game() : QGraphicsView(), scene(new QGraphicsScene)
{

    game_over = false;
    controller1 = new Controller();
    controller2 = new Controller();

    EntitySquare *border_top = new EntitySquare(this, 0, -10, 2, 800, 0.0,  ":/imagens/transparent.png");
    border_top->setMass(std::numeric_limits<float>::max());
    screen_borders.push_back(border_top);

    EntitySquare *border_bottom = new EntitySquare(this, 0, 600, 2, 800, 0.0, ":/imagens/transparent.png");
    border_bottom->setMass(std::numeric_limits<float>::max());
    screen_borders.push_back(border_bottom);

    EntitySquare *border_left = new EntitySquare(this, -10, 0, 600, 2, 0.0,  ":/imagens/transparent.png");
    border_left->setMass(std::numeric_limits<float>::max());
    screen_borders.push_back(border_left);

    EntitySquare *border_right = new EntitySquare(this, 800, 0, 600, 2, 0.0,  ":/imagens/transparent.png");
    border_right->setMass(std::numeric_limits<float>::max());
    screen_borders.push_back(border_right);

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
    //run();
}

void Game::run(){
    update_timer.start();
}

void Game::stop(){
    update_timer.stop();
}

void Game::addEntity(Entity* ent){
    entity_list.push_back(ent);
    scene->addItem(ent->getQitem());
}

void Game::addGraphic(Image *img){
    scene->addItem(img->getQitem());
}

void Game::clearGraphics(){
    scene->clear();
}

void Game::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left)
        controller1->left = 1;
    else if(event->key() == Qt::Key_Right)
        controller1->right = 1;
    else if(event->key() == Qt::Key_Up)
        controller1->up = 1;
    else
        controller1->down = 1;

}

void Game::keyReleaseEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left)
        controller1->left = 0;
    else if(event->key() == Qt::Key_Right)
        controller1->right = 0;
    else if(event->key() == Qt::Key_Up)
        controller1->up = 0;
    else
        controller1->down = 0;

}

void Game::update(){

    static int x = 0;
    Vector normal;



    for(int i = 0; i < entity_list.size(); i++){
        for(int k = 0; k < entity_list.size(); k++){

            if(game_over)
                return;

            if(k == i)
                continue;

            if(entity_list[i]->collidesWith(entity_list[k], &normal)){
                entity_list[i]->onCollision(*(entity_list[k]), &normal);
            }



        }
    }


    for(Entity *ent : entity_list)
        ent->update();

}

