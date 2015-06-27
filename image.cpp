#include "image.h"

Image::Image(int x, int y, int height, int width, float angle)
{
    item = NULL;

    setHeight(height);
    setWidth(width);
    setPosition(x, y);
    setAngle(angle);

}

void Image::setX(float x) {
    this->x = x;
    setPosition(x, y);
}
void Image::setY(float y) {
    this->y = y;
    setPosition(x, y);
}

void Image::setPosition(float x, float y) {

    this->x = x;
    this->y = y;

    center.setX(x + width/2);
    center.setY(y + height/2);

    if(item != NULL)
        item->setPos(x,y);

}

void Image::setHeight(int height) {

    this->height = height;
    edge.bottom = height/2;
    edge.top = - height/2;
    center.setY(y + height/2);

    if(item != NULL)
        item->update(x,y, width, height);

}

void Image::setWidth(int width) {

    this->width = width;
    edge.left = - width/2;
    edge.right = width/2;
    center.setX(x + width/2);

    if(item != NULL)
        item->update(x,y, width, height);
}

void Image::setDimensions(int width, int height){

    setHeight(height);
    setWidth(width);
}

void Image::setAngle(float angle) {

    if(angle > 360.0){
        while(angle > 360.0)
            this->angle = angle - 360.0;
    } else if(angle < 0.0){
        angle = angle + 360.0;
        while(angle < 0.0)
            angle = angle + 360.0;
    }

    this->angle = angle;

    if(item != NULL)
        item->setRotation(angle);

}

BitmapImage::BitmapImage(string bitmap, int x, int y, int height, int width, float angle) :   Image(x,y,height,width, angle) {

    item = new QGraphicsPixmapItem();
    dynamic_cast<QGraphicsPixmapItem*>(item)->setPixmap((QString::fromStdString(bitmap)));
    item->update(x,y,width,height);
}

SquareImage::SquareImage(int x, int y, int height, int width, float angle) : Image(x,y,height,width, angle){

    item = new QGraphicsRectItem(x,y,height, width);
    item->update(x,y, height, width);
}

TextBoxImage::TextBoxImage(int x, int y, string txt) : Image(x, y, 0, 0, 0) , text(txt) {

    item = new QGraphicsTextItem(QString::fromStdString(txt));
    item->setX(x); item->setY(y);

}

#define LETTER_WIDTH 10
#define LETTER_HEIGHT 20

void TextBoxImage::setText(string txt){

    text = txt;
    color = BLACK;

    dynamic_cast<QGraphicsTextItem*>(item)->setPlainText(QString::fromStdString(txt));

}
