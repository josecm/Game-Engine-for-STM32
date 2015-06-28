#include "menu.h"

MenuLine::MenuLine(int x, int y, string option, bool(*opt)(Game *)) : TextBoxImage(x, y, option),
    option(opt) {

}


MenuFrame::MenuFrame(int x , int y) : SquareImage(x, y), option_selected(NULL), max_line_length(0),
    num_options(0), lineHeight(TEXT_SMALL), option_selected_index(0) {

}

void MenuFrame::addMenuLine(MenuLine* option, int position){

    option->setColor(BLACK);
    option->setTextSize(TEXT_SMALL);


    if(position > num_options)
        position = num_options + 1;
    else if(position < 1)
        position = 1;

    if(option_selected == NULL || position == option_selected_index - 1){
        if(option_selected != NULL){
            option_selected->setColor(BLACK);
        }
        option_selected = option;
        option_selected->setColor(RED);
    }

    options_menu.insert(options_menu.begin() + position - 1, option);

    if(option->getWidth() > max_line_length) {
        max_line_length = option->getWidth();
        setWidth(max_line_length + 2 * MENU_H_MARGINS);

        for(MenuLine* line : options_menu){
            int x = (getWidth() - line->getWidth() / 2) +  getX();
            line->setX(x);
        }

    }

    int x = (getWidth() - option->getWidth() / 2) +  getX();
    option->setX(x);

    int y = (position - 1) * (MENU_LINE_SPACING + lineHeight) + MENU_V_MARGINS + getY();
    option->setY(y);

    if(position <= num_options){
        for(int i = num_options; i <= options_menu.size(); i++){

            int y = (i - 1) * (MENU_LINE_SPACING + lineHeight) + MENU_V_MARGINS + getY();
            options_menu[i - 1]->setY(y);

        }
    }

    setHeight(getHeight() + lineHeight);

    num_options++;

}

bool MenuFrame::selectOption(int i){

    if(i < 0 || i >= num_options)
        return false;

    option_selected->setColor(BLACK);
    option_selected = options_menu[i];
    option_selected->setColor(RED);
    option_selected_index = i;

    return false;

}

bool MenuFrame::nextOption(){

    return selectOption(option_selected_index + 1);

}

bool MenuFrame::prevOption(){

    return selectOption(option_selected_index - 1);

}

void MenuFrame::setPosition(int x, int y){

    Image::setPosition(x, y);

    for(MenuLine* line : options_menu){
        int x = (getWidth() - line->getWidth() / 2) +  getX();
        line->setX(x);
    }

    for(int i = 1; i <= options_menu.size(); i++){

        int y = (i - 1) * (MENU_LINE_SPACING + lineHeight) + MENU_V_MARGINS + getY();
        options_menu[i - 1]->setY(y);

    }

}

void MenuFrame::startMenuFrame(Game *game){

    game->addGraphic(this);

    for(Image* img: options_menu)
        game->addGraphic(img);

}

void MenuFrame::endMenuFrame(Game *game){

    game->removeGraphic(this);

    for(Image* img: options_menu)
        game->removeGraphic(img);

}

Menu::Menu(Game* game, MenuFrame *init, Controller *in = NULL) :  game(game), initial_frame(init), input(in){

}

void Menu::addInput(Controller *in) { input = in; }

void Menu::startMenu(){

    framestack.push(initial_frame);
    initial_frame->startMenuFrame(game);

}

void Menu::endMenu(){

    MenuFrame *frame;

    while(!framestack.empty()){
        frame = framestack.top();
        frame->endMenuFrame(game);
        framestack.pop();
    }

}

void Menu::pushMenu(MenuFrame *frame){

    MenuFrame *tempframe = framestack.top();
    tempframe->endMenuFrame(game);
    frame->startMenuFrame(game);
    framestack.push(frame);

}

void Menu::popMenu(){

    MenuFrame *tempframe = framestack.top();
    tempframe->endMenuFrame(game);
    framestack.pop();
    tempframe = framestack.top();
    tempframe->startMenuFrame(game);

}

void Menu::readInput(){

    MenuFrame *tempframe = framestack.top();

    if(input->up)
        tempframe->prevOption();
    if(input->down)
        tempframe->nextOption();
    if(input->space)
        tempframe->option_selected->option(game);

}
