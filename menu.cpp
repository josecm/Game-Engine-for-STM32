#include "menu.h"

MenuLine::MenuLine(int x, int y, string option, bool(*opt)(Menu *)) : TextBoxImage(x, y, option),
    option(opt) {

}

bool returnOption(Menu *menu){

    menu->popMenu();

}


MenuLineReturn::MenuLineReturn(int x, int y) :  MenuLine(x, y, "RETURN", returnOption) {

}

bool nextFrameOption(Menu *menu){


    MenuLineNextFrame *line = dynamic_cast<MenuLineNextFrame*>(menu->peekMenu()->getOptionSelected());
    menu->pushMenu(line->next);


}

MenuLineNextFrame::MenuLineNextFrame(MenuFrame* nxt, string str, int x, int y) : MenuLine(x, y, str, nextFrameOption), next(nxt) {

}

MenuFrame::MenuFrame() : SquareImage(), option_selected(NULL), max_line_length(0),
    num_options(0), lineHeight(TEXT_SMALL), option_selected_index(0) {

    parentmenu = NULL;
    setColor(WHITE);

}

void MenuFrame::Center(){

    int x = (800 - getWidth()) / 2;
    int y = (600 - getHeight()) / 2;

    setPosition(x, y);

}

void MenuFrame::addMenuLine(MenuLine* option, int position){

    option->setColor(BLACK);
    option->setTextSize(TEXT_SMALL);

    if(position > num_options)
        position = num_options;
    else if(position < 0)
        position = 0;

    if(option_selected == NULL || position == option_selected_index){
        if(option_selected != NULL){
            option_selected->setColor(BLACK);
        }
        option_selected = option;
        option_selected->setColor(RED);
    }

    options_menu.insert(options_menu.begin() + position, option);



    if(option->getWidth() > max_line_length) {
        max_line_length = option->getWidth();
        setWidth(max_line_length + MENU_H_MARGINS * 2);
    }

    num_options++;

    setHeight((num_options + 1)  * (lineHeight+ MENU_LINE_SPACING) +  MENU_V_MARGINS );

    Center();

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
        int xx = ((getWidth() - line->getWidth()) / 2) +  getX() - MENU_LINE_INDENT;
        line->setX(xx);
    }

    for(int i = 0; i < options_menu.size(); i++){
        int yy = i * (MENU_LINE_SPACING + lineHeight) + MENU_V_MARGINS + getY();// - MENU_LINE_INDENT;
        options_menu[i]->setY(yy);
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

    frame->parentmenu = this;
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

    if(input->right)
        game->pause(false);
    if(input->up)
        tempframe->prevOption();
    if(input->down)
        tempframe->nextOption();
    if(input->space)
        tempframe->option_selected->option(this);

    input->right = input->down = input->left = input->up = input->space =  0;

}
