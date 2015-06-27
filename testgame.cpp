#include "testgame.h"

TestGame::TestGame() : Game()
{
    counter = 0;
    message = new TextBoxImage(750, 50, "0");
    message2 = new TextBoxImage(250, 350, "GAME OVER");

    player = new Player(this, 25,25);
    player->setInput(controller1);
    addEntity(player);

    finish = new EntitySquare(this ,700, 500, 50, 50,0.0, ":/imagens/finishline.png");
    finish->setMass(std::numeric_limits<float>::max());
    addEntity(finish);

    Wall *wall;
    wall = new Wall(this, 100, 0); addEntity(wall);
    wall = new Wall(this, 250, 200); addEntity(wall);
    wall = new Wall(this, 400, 0); addEntity(wall);
    wall = new Wall(this, 550, 200); addEntity(wall);
    //wall = new Wall(this, 700, 0); addEntity(wall);

    addGraphic(message);

}

Player::Player(Game *game, int x, int y) : EntityCircle(game, x, y, 25, ":/imagens/circle50.png") {

    setVelocity(0.0, 0.0);
}

void Player::update(){

    if(input){
        if(input->left)
            velocity.setX(velocity.getX() - 0.1);
        if(input->right)
            velocity.setX(velocity.getX() + 0.1);
        if(input->up)
            velocity.setY(velocity.getY() - 0.1);
        if(input->down)
            velocity.setY(velocity.getY() + 0.1);
    }

    EntityCircle::update();
}

void Player::onCollision(Entity &ent, Vector *mtd) {

    static TestGame *testgame = dynamic_cast<TestGame*>(game);

    if(&ent == testgame->finish){

        if(mtd->getLength() > (ent.getWidth()) / 2){
            setPosition(25,25); setVelocity(0.0, 0.0);
            (testgame->counter)++;
            ostringstream stream;
            stream << testgame->counter;
            testgame->message->setText(stream.str());
        }
     }
     else if(typeid(ent) == typeid(Wall)){
         qDebug() << "Collides with wall";
         if(mtd->getLength() > getWidth() / 2){
            testgame->clearGraphics();
            testgame->addGraphic(testgame->message2);
            testgame->game_over = true;
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
