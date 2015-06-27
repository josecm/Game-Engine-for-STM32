#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QString>
#include <QWidget>
#include <cmath>
#include <iostream>
#include "Vector.h"

using namespace std;

typedef struct {

    int left;
    int right;
    int top;
    int bottom;

} EDGE;

class Image
{

protected:
    float x;
    float y;
    int height;
    int width;
    EDGE edge;
    Vector center;

    char color;
    char filled;

    float angle;

    QGraphicsItem *item;

public:
    Image(int x = 0, int y = 0, int heigth = 10, int width = 10, float angle = 0.0);

    virtual void setPosition(float x, float y);
    virtual void setX(float x);
    virtual void setY(float y);
    virtual void setHeight(int height);
    virtual void setWidth(int width);
    virtual void setDimensions(int, int);


    virtual void setAngle(float angle);

    virtual float getX() { return x;}
    virtual float getY() { return y;}
    virtual int getHeight() { return height; }
    virtual int getWidth() { return width; }
    virtual float getAngle() { return angle; }
    Vector& getCenter() { return center; }

    QGraphicsItem * getQitem() { return item; }

};



class BitmapImage : public Image {

public:
    BitmapImage(string bitmap = ":/imagens/transparent.png", int x = 0, int y = 0, int heigth = 10, int width = 10, float angle = 0.0);

};

class SquareImage : public Image {

public:
    SquareImage( int x = 0, int y = 0, int heigth = 10, int width = 10, float angle = 0.0);

};

class CircleImage : public Image{

    float radius;
    int x_center, y_center;

public:
    CircleImage(int x = 0, int y = 0, int heigth = 10, int width = 10, float angle = 0.0);

};

class TextBoxImage: public Image{

    string text;


public:
    TextBoxImage(int x = 0, int y = 0, string txt = "");
    void setText(string txt);
};

//TODO
//class PointImage
//class LineImage

#endif // IMAGE_H
