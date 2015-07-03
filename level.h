#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "image.h"
#include "entity.h"
#include "gameview.h"

using namespace std;

class Level
{

protected:
    Game *game;
    vector<Entity*> entity_list;
    vector<Image*> graphics_list;

public:
    Level(Game* game);

    void startlevel();
    void endlevel();

    virtual void initialize() { }
    virtual void finalize() { }

    void addEntity(Entity *ent) { entity_list.push_back(ent); }
    void addGraphic(Image *img) { graphics_list.push_back(img); }

};

#endif // LEVEL_H
