#include "testgame.h"


bool linefunc(Menu* menu){

    return true;
}

bool linereturnpause(Menu* menu){

    menu->getGame()->pause(false);

    return true;
}

TestGame::TestGame() : Game()
{

   MenuFrame *pauseinit = new MenuFrame();
   MenuFrame *pause2 = new MenuFrame();

   MenuLine *line1 = new MenuLine(0, 0, "NAO FAZ NADA1", linefunc);
   MenuLine *line2 = new MenuLine(0, 0, "NAO FAZ NADA2", linefunc);
   MenuLine *continueline = new MenuLine(0,0, "CONTINUE", linereturnpause);

   MenuLineReturn *linereturn = new MenuLineReturn();
   MenuLineNextFrame *linenext = new MenuLineNextFrame(pause2, "NEXT FRAME");

   pauseinit->addMenuLine(continueline);
   pauseinit->addMenuLine(linenext);
   pauseinit->addMenuLine(line1);
   pause2->addMenuLine(linereturn);
   pause2->addMenuLine(line2);

   Menu *pausemenu = new Menu(this, pauseinit, controller1);
   setMenuPaused(pausemenu);

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
   TestLevel *level2 = new TestLevel(this, 25, 25, 700, 500);

   Wall *wall;
   wall = new Wall(this, 100, 0); level1->addEntity(wall); level2->addEntity(wall);
   wall = new Wall(this, 250, 100); level1->addEntity(wall);
   wall = new Wall(this, 400, 0); level1->addEntity(wall);
   wall = new Wall(this, 550, 100); level1->addEntity(wall); level2->addEntity(wall);
   //wall = new Wall(this, 700, 0); addEntity(wall);

   addLevel(level2);
   addLevel(level1);

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
