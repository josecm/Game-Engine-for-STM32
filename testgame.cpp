#include "testgame.h"

bool line1func(Game* game){

    game->pause(false);
    return true;
}

bool line2func(Game* game){

    return true;
}

TestGame::TestGame() : Game()
{

   MenuLine *line1 = new MenuLine(0, 0, "RETURN", line1func);
   MenuLine *line2 = new MenuLine(0, 0, "NAO FAZ NADA", line2func);
   MenuFrame *pauseinit = new MenuFrame(200,300);
   pauseinit->addMenuLine(line1);
   pauseinit->addMenuLine(line2);

   Menu *pausemenu = new Menu(this, pauseinit, controller1);

   setMenuPaused(pausemenu);

   SquareImage *sqr = new SquareImage(10, 10, 10, 10);
   addGraphic(sqr);
   sqr->setDimensions(100, 100);

   counter = 0;
   message = new TextBoxImage(750, 50, "0");
   addGraphic(message);

   player = new Player(this, 25,25);
   player->setInput(controller1);
   addEntity(player);

   finish = new EntitySquare(this ,700, 500, 50, 50,0.0, ":/imagens/finishline.png");
   finish->setMass(std::numeric_limits<float>::max());
   addEntity(finish);


   // NIVEL 1

   TestLevel *level1 = new TestLevel(this, 25, 25, 700, 500);
   TestLevel *level2 = new TestLevel(this, 25, 100, 700, 500);

   Wall *wall;
   wall = new Wall(this, 100, 0); level1->addEntity(wall); level2->addEntity(wall);
   wall = new Wall(this, 250, 200); level1->addEntity(wall);
   wall = new Wall(this, 400, 0); level1->addEntity(wall); level2->addEntity(wall);
   wall = new Wall(this, 550, 200); level1->addEntity(wall);
   //wall = new Wall(this, 700, 0); addEntity(wall);

   addLevel(level1);
   addLevel(level2);


}

Player::Player(Game *game, int x, int y) : EntityCircle(game, x, y, 25, ":/imagens/circle50.png") {

    setVelocity(0.0, 0.0);
}

void Player::readInput(){

    if(input){
        if(input->left)
            velocity.setX(velocity.getX() - 0.1);
        if(input->right)
            velocity.setX(velocity.getX() + 0.1);
        if(input->up)
            velocity.setY(velocity.getY() - 0.1);
        if(input->down)
            velocity.setY(velocity.getY() + 0.1);
        if(input->p_button)
            game->pause(true);
    }

}

void Player::onCollision(Entity &ent, Vector *mtd) {

    static TestGame *testgame = dynamic_cast<TestGame*>(game);

    if(&ent == testgame->finish){

        if(mtd->getLength() > (ent.getWidth()) / 2){
            setPosition(25,25);
            setVelocity(0.0, 0.0);

            game->levelOver(true);
        }
     }
     else if(typeid(ent) == typeid(Wall)){
         if(mtd->getLength() > getWidth() / 2){
            game->levelOver(false);
         }
     }
     else {
        bounce(ent, mtd);
     }

}

Wall::Wall(Game* game, int x, int y) : EntitySquare(game, x, y, 500, 50, 0.0, ":/imagens/wall50x500.png") {

    setMass(std::numeric_limits<float>::max());
    setDamping(0.15);
    setFriction(0.15);

}
