#ifndef MENU_H
#define MENU_H

#include <cstdarg>
#include <stack>
#include "gameview.h"
#include "controller.h"
#include "image.h"

#define MENU_H_MARGINS 20
#define MENU_V_MARGINS 20
#define MENU_LINE_SPACING 5
#define MENU_LINE_INDENT 3

using namespace std;
class Game;
class Menu;
class MenuFrame;

class MenuLine : public TextBoxImage{

public:

    MenuLine(int x, int y, string option, bool (*opt)(Menu*));
    bool (*option)(Menu *);

};


class MenuLineReturn : public MenuLine {

public:
    MenuLineReturn(int x = 0, int y = 0);

};

class MenuLineNextFrame : public MenuLine {

     friend bool nextFrameOption(Menu *);

    MenuFrame *next;
public:
    MenuLineNextFrame(MenuFrame* nxt, string str, int x = 0, int y = 0);
};

class MenuFrame : public SquareImage  {

    friend class Menu;
    friend class MenuLine;

    Menu* parentmenu;
    vector<MenuLine*> options_menu;
    MenuLine *option_selected;
    int num_options;
    int max_line_length;
    int lineHeight;
    int option_selected_index;

    COLOR background_color;

public:
    MenuFrame();
    void addMenuLine(MenuLine*, int position = 0);
    void startMenuFrame(Game *game);
    void endMenuFrame(Game *game);
    bool selectOption(int);
    bool nextOption();
    bool prevOption();
    void setPosition(int x, int y);
    void Center();
    MenuLine* getOptionSelected() { return option_selected; }

};

class Menu
{

    friend class MenuFrame;

    Game *game;
    Controller *input;
    MenuFrame *initial_frame;
    stack<MenuFrame*> framestack;

public:
    Menu(Game* game,MenuFrame *init, Controller *in);
    Game* getGame() { return game; }
    void addInput(Controller *in);
    void startMenu();
    void endMenu();
    void pushMenu(MenuFrame*);
    void popMenu();
    MenuFrame* peekMenu() { return framestack.top(); }
    virtual void readInput();
};

#endif // MENU_H
