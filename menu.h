#ifndef MENU_H
#define MENU_H

#include <cstdarg>
#include <stack>
#include "gameview.h"
#include "controller.h"
#include "image.h"

#define MENU_H_MARGINS 10
#define MENU_V_MARGINS 10
#define MENU_LINE_SPACING 5

using namespace std;
class Game;

class MenuLine : public TextBoxImage{


public:

    MenuLine(int x, int y, string option, bool (*opt)(Game*));
    bool (*option)(Game *);
};

class MenuFrame : public SquareImage  {

    friend class Menu;

    vector<MenuLine*> options_menu;
    MenuLine *option_selected;
    int num_options;
    int max_line_length;
    int lineHeight;
    int option_selected_index;


public:
    MenuFrame(int x= 0 , int y = 0);
    void addMenuLine(MenuLine*, int position = 1);
    void startMenuFrame(Game *game);
    void endMenuFrame(Game *game);
    bool selectOption(int);
    bool nextOption();
    bool prevOption();
    void setPosition(int x, int y);

};

class Menu
{
    Game *game;
    Controller *input;
    MenuFrame *initial_frame;
    stack<MenuFrame*> framestack;

public:
    Menu(Game* game,MenuFrame *init, Controller *in);
    void addInput(Controller *in);
    void startMenu();
    void endMenu();
    void pushMenu(MenuFrame*);
    void popMenu();
    virtual void readInput();
};

#endif // MENU_H
