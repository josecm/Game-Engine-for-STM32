#include "level.h"

Level::Level(Game *game) : game(game)
{
}

void Level::startlevel(){

    for(Entity* ent: entity_list)
        game->addEntity(ent);

    for(Image* img: graphics_list)
        game->addGraphic(img);

    initialize();
}

void Level::endlevel(){

    for(Entity* ent: entity_list)
        game->removeEntity(ent);

    for(Image* img: graphics_list)
        game->removeGraphic(img);

}
