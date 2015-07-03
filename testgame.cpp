#include "testgame.h"

void TestLevel::initialize() {

    static TestGame *testgame = dynamic_cast<TestGame*>(game);

    testgame->addEntity(testgame->player);
    testgame->player->setPosition(px,py);
    testgame->player->setVelocity(0.0, 0.0);
    testgame->addEntity(testgame->finish);
    testgame->finish->setPosition(fx,fy);
    testgame->addGraphic(testgame->message);


    if(game->isLevelOverSuccess()){
        (testgame->counter)++;
        ostringstream stream;
        stream << testgame->counter;
        testgame->message->setText(stream.str());
     }

}

void TestLevel::finalize() {

    static TestGame *testgame = dynamic_cast<TestGame*>(game);

    testgame->removeEntity(testgame->player);
    testgame->removeEntity(testgame->finish);
    testgame->removeGraphic(testgame->message);

}

bool linefunc(Menu* menu){

    return true;

}

bool startgame(Menu* menu){

    menu->getGame()->run();
    return true;

}

bool returntomainmenu(Menu* menu){

    menu->endMenu();
    menu->getGame()->goToInitialMenu();
    return true;
}

TestGame::TestGame() : Game()
{

    //SCORE BOARD

    counter = 0;
    message = new TextBoxImage(750, 50, "0");
    message->setTextSize(TEXT_LARGE);

    //ENTITYS

    player = new Player(this, 25,25);
    player->setInput(controller1);

    finish = new EntitySquare(this ,700, 500, 50, 50,0.0, ":/imagens/finishline.png");
    finish->setMass(std::numeric_limits<float>::max());


    // MENUS

    MenuFrame *pauseinit = new MenuFrame();
    MenuFrame *pause2 = new MenuFrame();

    MenuLine *line1 = new MenuLine(0, 0, "NAO FAZ NADA1", linefunc);
    MenuLine *line2 = new MenuLine(0, 0, "NAO FAZ NADA2", linefunc);
    MenuLine *returntomain = new MenuLine(0,0, "RETURN TO MAIN MENU", returntomainmenu);
    MenuLineContinue *continueline = new MenuLineContinue();

    MenuLinePrevFrame *linereturn = new MenuLinePrevFrame();
    MenuLineNextFrame *linenext = new MenuLineNextFrame(pause2, "NEXT FRAME");

    pauseinit->addMenuLine(continueline);
    pauseinit->addMenuLine(linenext);
    pauseinit->addMenuLine(line1);
    pause2->addMenuLine(linereturn);
    pause2->addMenuLine(line2);
    pause2->addMenuLine(returntomain);

    Menu *pausemenu = new Menu(this, pauseinit, controller1);
    setMenuPaused(pausemenu);

    MenuFrame *init = new MenuFrame();
    MenuLine *linestart = new MenuLine(0,0, "START GAME", startgame);
    init->addMenuLine(linestart);
    Menu *initmenu = new Menu(this, init, controller1);
    setMenuInitial(initmenu);

    // LEVELS

    TestLevel *level1 = new TestLevel(this, 25, 25, 700, 500);
    TestLevel *level2 = new TestLevel(this, 25, 25, 700, 500);
    TestLevel *level3 = new TestLevel(this, 25, 275, 700, 275);

    Wall *wall;
    wall = new WallBig(this, 100, 0); level1->addEntity(wall); level2->addEntity(wall);
    wall = new WallBig(this, 250, 100); level1->addEntity(wall);
    wall = new WallBig(this, 400, 0); level1->addEntity(wall);
    wall = new WallBig(this, 550, 100); level1->addEntity(wall); level2->addEntity(wall);
    //wall = new Wall(this, 700, 0); addEntity(wall);

    wall = new WallMedium(this, 100, 100); level3->addEntity(wall);
    wall = new WallSmall(this, 250, 0); level3->addEntity(wall);
    wall = new WallSmall(this, 250, 175); level3->addEntity(wall);
    wall = new WallSmall(this, 250, 325); level3->addEntity(wall);
    wall = new WallSmall(this, 250, 500); level3->addEntity(wall);

    addLevel(level3);
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

        if(mtd->getLength() > (ent.getWidth()) / 3){
            setPosition(25,25);
            setVelocity(0.0, 0.0);

            game->levelOver(true);
        }
     }
     //else if(typeid(ent) == typeid(Wall)){
     else if(dynamic_cast<Wall*>(&ent)){
         if(mtd->getLength() > getWidth() / 2){
            game->levelOver(false);
         }
     }
     else {
        bounce(ent, mtd);
     }

}

Wall::Wall(Game* game, int x, int y, int height, int width, string wallpic) : EntitySquare(game, x, y, height ,width, 0.0, wallpic) {

    setMass(std::numeric_limits<float>::max());
    setDamping(0.15);
    setFriction(0.15);

}

WallBig::WallBig(Game* game, int x, int y) : Wall(game, x, y, 500, 50, ":/imagens/wall50x500.png") { }

WallMedium::WallMedium(Game* game, int x, int y) : Wall(game, x, y, 400, 50, ":/imagens/wall50x400.png") { }

WallSmall::WallSmall(Game* game, int x, int y) : Wall(game, x, y, 100, 50, ":/imagens/wall50x100.png") { }
