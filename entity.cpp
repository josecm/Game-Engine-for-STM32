#include "entity.h"

Entity::Entity(Game *game, int x, int y, int heigth, int width, float angle, string bitmap):
    BitmapImage(bitmap, x, y, heigth, width, angle), velocity(0.0,0.0), deltaV(0.0, 0.0)
{
    input = NULL;

    this->game = game;
    damping = 0.0;
    friction = 0.0;
    mass = 1.0;
    fixed = false;
    active = true;

}

void Entity::update(){

    velocity += deltaV;

    deltaV.setX(0.0); deltaV.setY(0.0);

    setPosition(x + velocity.getX(), y + velocity.getY());

}

void Entity::readInput(){ }

void Entity::onCollision(Entity &ent, Vector * mtd){

    bounce(ent, mtd);

}

bool Entity::collidesWith(Entity *ent, Vector *normal){

    if(!active || !(ent->isActive()))
        return false;

    if(ent->col_type == SQUARE)
        return collideSquare(dynamic_cast<EntitySquare*>(ent), normal);

    if(ent->col_type == CIRCLE)
        return collideCircle(dynamic_cast<EntityCircle*>(ent), normal);

    return false;

}

void Entity::setVelocity(float x, float y){

    velocity.setX(x);
    velocity.setY(y);

}

void Entity::setMass(float mass){

    this->mass = mass;
    if(fabs(mass - std::numeric_limits<float>::max()) < 0.00001)
        fixed = true;
    else
        fixed = false;
}

void Entity::setFixed(bool tf){

    fixed = tf;
    if(tf)
        mass = std::numeric_limits<float>::max();
    else
        mass = getWidth() * getHeight() / 1000;
}

void Entity::setDamping(float damp){

    if(damp > 1.0)
        damping = 1.0;
    if(damp < 0.0)
        damping = 0.0;
    else
        damping = damp;

}

float Entity::getDamping(){
    return damping;
}

void Entity::setFriction(float fric){

    if(fric > 1.0)
        friction = 1.0;
    if(fric < 0.0)
        friction = 0.0;
    else
        friction = fric;

}

float Entity::getFriction(){
    return friction;
}

void Entity::bounce(Entity &ent, Vector *normal){

    Vector Vdiff = ent.velocity - velocity;
    Vector cUV = ent.center - center;


    float massRatio = 1.0f;
    if(mass != 0)
          massRatio *= ent.mass / (mass + ent.mass);

    if(cUV.dotProduct(*normal) < 0.0)
        normal->reverse();



    if(col_type == SQUARE || ent.col_type == SQUARE){
        cUV = *normal;
    }

    float dx = cUV.getX();
    float dy = cUV.getY();

    cUV.normalize();


    float cUVdotVdiff = cUV.dotProduct(Vdiff);
    float damp = (damping + ent.damping) / 2.0;
    float fric = (friction + ent.friction) / 2.0;

    if(cUVdotVdiff > 0)
         //setPosition(x - cUV.getX() * massRatio, y - cUV.getY() * massRatio);
         setPosition(x - dx * massRatio, y - dy * massRatio);
    else{

        Vector temp = (cUV * (2.0 * massRatio * cUVdotVdiff)) * (1 - damp);

        if(fric > 0.0){
            Vector temp2 = cUV;
            temp2.reverse();
            temp2.setLength(temp2.dotProduct(Vdiff));
            temp2 = Vdiff - temp2;
            temp2 *= fric;
            temp += temp2 * massRatio;
        }

        deltaV += temp;

    }

}

EntitySquare::EntitySquare(Game *game, int x, int y, int heigth, int width, float angle, string bitmap)
    : Entity(game, x, y, heigth, width, angle, bitmap){

    col_type = SQUARE;
    rotatedBoxReady = false;

}

void EntitySquare::update(){

    if(input){
        //ISTO VAI TER DE SAIR DAQUI - IMPLEMENTAR CONTROLLER (DE ALGUMA FORMA CONECTADA AO JOGO E A ENTIDADE
        /*
        if(left)
            velocity.rotate(-1.0);
        if(right)
            velocity.rotate(1.0);
        if(up)
            velocity *= 1.01;
        if(down)
            velocity *= 0.99;
         */
        if(input->left)
            velocity.rotate(5.0);
        //velocity.setAngle(180.0);
        if(input->right)
            velocity.rotate(-5.0);
        //velocity.setAngle(0.0);
        if(input->up){

            if(velocity.getLength() < 0.001){
                velocity.stretch(1.0);
            }
            velocity *= 1.01;

            //velocity.setAngle(270.0);
        }
        if(input->down)
            //velocity.setAngle(90.0);
            velocity *= 0.99;

        /*
        if(left)
            velocity.setX(velocity.getx - 0.05);
        if(right)
            velocity.setX(velocity.getx + 0.05);
        if(up)
            velocity.setY(velocity.gety - 0.05);
        if(down)
             velocity.setY(velocity.gety + 0.05);
        */

        //...................................................................................................
    }

    Entity::update();

    if(x + width > 800 || x < 0)
        velocity.reverseX();

    if(y + height > 600 || y < 0)
        velocity.reverseY();

    if(x + width > 800)
        setPosition(800 - width, y);
    else if(x < 0)
        setPosition(0, y);

    if(y + height > 600)
        setPosition(x, 600 - height);
    else if(y < 0)
        setPosition(x, 0);

    rotatedBoxReady = false;
 }

void EntitySquare::computeRotatedBox(){

    if(rotatedBoxReady)
        return;

    float projection;
    Vector rotatedX(cos(angle/180.0 * M_PI), sin(angle/180.0 * M_PI));
    Vector rotatedY(-sin(angle/180.0 * M_PI), cos(angle/180.0 * M_PI));


    corners[0] = center + (rotatedX * static_cast<float>(edge.left) ) + (rotatedY * static_cast<float>(edge.top) );
    corners[1] = center + (rotatedX * static_cast<float>(edge.right)) + (rotatedY * static_cast<float>(edge.top));
    corners[2] = center + (rotatedX * static_cast<float>(edge.right)) + (rotatedY * static_cast<float>(edge.bottom));
    corners[3] = center + (rotatedX * static_cast<float>(edge.left)) + (rotatedY * static_cast<float>(edge.bottom));


    edge01 = corners[1] - corners[0];
    edge01.normalize();
    edge03 = corners[3] - corners[0];
    edge03.normalize();

    projection = edge01.dotProduct(corners[0]);
    edge01Min = edge01Max = projection;

    projection = edge01.dotProduct(corners[1]);
    if(projection < edge01Min)
        edge01Min = projection;
    else if(projection > edge01Max)
         edge01Max = projection;

    projection = edge03.dotProduct(corners[0]);
    edge03Min = edge03Max = projection;

    projection = edge03.dotProduct(corners[3]);
    if(projection < edge03Min)
        edge03Min = projection;
    else if(projection > edge03Max)
         edge03Max = projection;

    rotatedBoxReady = true;

}

bool EntitySquare::projectionOverlap(EntitySquare *ent, Vector *normal){

    float projection, min01, max01, min03, max03;
    float int_min1 = 0.0, int_min3 = 0.0;

    projection = edge01.dotProduct(ent->corners[0]);
    min01 = max01 = projection;

    for(int i = 1; i <= 3; i++){
        projection = edge01.dotProduct(ent->corners[i]);
        if(projection < min01)
            min01 = projection;
        else if(projection > max01)
            max01 = projection;
    }

    if(min01 >= edge01Max || max01 <= edge01Min)
        return false;

    if(min01 >= edge01Min && max01 <= edge01Max)
        int_min1 = max01 - min01;
    else  if(min01 <= edge01Min && max01 >= edge01Max)
        int_min1 = edge01Max - edge01Min;
    else if(min01 <= edge01Max && min01 >= edge01Min)
        int_min1 = edge01Max - min01;
     else if(max01 >= edge01Min && max01 <= edge01Max)
        int_min1 = max01 - edge01Min;

    projection = edge03.dotProduct(ent->corners[0]);
    min03 = max03 = projection;

    for(int i = 1; i <= 3; i++){
        projection = edge03.dotProduct(ent->corners[i]);
        if(projection < min03)
            min03 = projection;
        else if(projection > max03)
            max03 = projection;
    }

    if(min03 >= edge03Max || max03 <= edge03Min)
        return false;

    if(min03 >= edge03Min && max03 <= edge03Max)
        int_min3 = max03 - min03;
    else  if(min03 <= edge03Min && max03 >= edge03Max)
        int_min3 = edge03Max - edge03Min;
    else if(min03 <= edge03Max && min03 >= edge03Min)
        int_min3 = edge03Max - min03;
     else if(max03 >= edge03Min && max03 <= edge03Max)
        int_min3 = max03 - edge03Min;

    if(int_min1 < int_min3){
        *normal = edge01;
        normal->setLength(int_min1);
    }
    else{
        *normal = edge03;
        normal->setLength(int_min3);
    }


    normal->reverse();
    return true;
}

bool EntitySquare::collideSquare(EntitySquare* ent, Vector *normal){

    computeRotatedBox();
    ent->computeRotatedBox();

    if(projectionOverlap(ent, normal) && ent->projectionOverlap(this, normal)){
        return true;
    }

    return false;

}

bool EntitySquare::collideCircle(EntityCircle* ent, Vector *normal){

    float min01, min03, max01, max03, center01, center03;
    float int_min1, int_min3;
    computeRotatedBox();

    center01 = edge01.dotProduct(ent->getCenter());
    min01 = center01 - ent->getRadius();
    max01 = center01 + ent->getRadius();

    if(min01 >= edge01Max || max01 <= edge01Min)
        return false;

    if(min01 >= edge01Min && max01 <= edge01Max)
        int_min1 = max01 - min01;
    else  if(min01 <= edge01Min && max01 >= edge01Max)
        int_min1 = edge01Max - edge01Min;
    else if(min01 <= edge01Max && min01 >= edge01Min)
        int_min1 = edge01Max - min01;
     else if(max01 >= edge01Min && max01 <= edge01Max)
        int_min1 = max01 - edge01Min;

    center03 = edge03.dotProduct(ent->getCenter());
    min03 = center03 - ent->getRadius();
    max03 = center03 + ent->getRadius();

    if(min03 >= edge03Max || max03 <= edge03Min)
        return false;

    if(min03 >= edge03Min && max03 < edge03Max)
        int_min3 = max03 - min03;
    else  if(min03 <= edge03Min && max03 >= edge03Max)
        int_min3 = edge03Max - edge03Min;
    else if(min03 <= edge03Max && min03 >= edge03Min)
        int_min3 = edge03Max - min03;
     else if(max03 >= edge03Min && max03 <= edge03Max)
        int_min3 = max03 - edge03Min;

    //nestes casos o comprimento da normal nao esta de acordo com mtd
    if(center01 < edge01Min && center03 < edge03Min){
        normal->setAngle(225);
        normal->setLength(1.0);
        return collideCornerCircle(ent, corners[0]);
    }
    if(center01 > edge01Max && center03 < edge03Min){
        normal->setAngle(315);
        normal->setLength(1.0);
        return collideCornerCircle(ent, corners[1]);
    }
    if(center01 > edge01Max && center03 > edge03Max){
        normal->setAngle(45);
        normal->setLength(1.0);
        return collideCornerCircle(ent, corners[2]);
    }
    if(center01 < edge01Min && center03 > edge03Max){
        normal->setAngle(135);
        normal->setLength(1.0);
        return collideCornerCircle(ent, corners[3]);
    }

    //normal->normalize();
    if(int_min1 < int_min3){

        *normal = edge01;
        normal->setLength(int_min1);
    }
    else{
        *normal = edge03;
        normal->setLength(int_min3);
    }

    return true;

}

bool EntitySquare::collideCornerCircle(EntityCircle* ent, Vector &corner){

    Vector distSquared = corner - ent->getCenter();

    distSquared.setX(distSquared.getX() * distSquared.getX());
    distSquared.setY(distSquared.getY() * distSquared.getY());

    float radiusSquare = ent->getRadius() * ent->getRadius();

    if(distSquared.getX() + distSquared.getY() <= radiusSquare)
        return true;

    return false;

}



EntityCircle::EntityCircle(Game *game, int x, int y, int radius, string bitmap) : Entity(game, x, y, radius * 2, radius * 2, 0.0, bitmap){

    col_type = CIRCLE;
    this->radius = radius;

}

bool EntityCircle::collideSquare(EntitySquare *ent, Vector *normal){

    if(ent->collideCircle(this, normal)){
        normal->reverse();
        return true;
    }

    return false;
}

bool EntityCircle::collideCircle(EntityCircle *ent, Vector *normal) {

    Vector distSquared = center - ent->getCenter();

    distSquared.setX(distSquared.getX() * distSquared.getX());
    distSquared.setY(distSquared.getY() * distSquared.getY());

    float radiusSquare = ent->getRadius() + radius;
    radiusSquare *= radiusSquare;

    if(distSquared.getX() + distSquared.getY() <= radiusSquare){

        return true;
    }
    return false;

}

void EntityCircle::update() {

    Entity::update();


}
