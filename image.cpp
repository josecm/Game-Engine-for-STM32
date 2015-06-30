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
        item->setPos(x, y);

}

void Image::setHeight(int height) {

    this->height = height;
    edge.bottom = height/2;
    edge.top = - height/2;
    center.setY(y + height/2);

    if(item != NULL){
        if(typeid(*item) == typeid(QGraphicsRectItem) ){
           QGraphicsRectItem* shape = dynamic_cast<QGraphicsRectItem*>(item);
           QRectF rect = shape->rect();
           rect.setHeight(height);
           shape->setRect(rect);
        }
        //item->update(0,0, 600, 800);
    }

}

void Image::setWidth(int width) {

    this->width = width;
    edge.left = - width/2;
    edge.right = width/2;
    center.setX(x + width/2);

    if(item != NULL){
        if(typeid(*item) == typeid(QGraphicsRectItem) ){
           QGraphicsRectItem* shape = dynamic_cast<QGraphicsRectItem*>(item);
           QRectF rect = shape->rect();
           rect.setWidth(width);
           shape->setRect(rect);
        }
        //item->update(0,0, 600, 800);
    }
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

void Image::setColor(COLOR clr){

    color = clr;
    QAbstractGraphicsShapeItem* temp;
    QGraphicsTextItem *textitem;
    Qt::GlobalColor color;

    switch(clr){
        case(BLACK):
            color = Qt::black;
            break;

        case(WHITE):
            color = Qt::white;
            break;

        case(BLUE):
            color = Qt::blue;
            break;

        case(RED):
            color = Qt::red;
            break;

        case(GREEN):
            color = Qt::green;
            break;
    }

    if(temp = dynamic_cast<QAbstractGraphicsShapeItem*>(item)){
        temp->setBrush(color);
        //temp->setPen(QColor(color));
    } else if(textitem = dynamic_cast<QGraphicsTextItem*>(item)){
        textitem->setDefaultTextColor(color);
    }

}

BitmapImage::BitmapImage(string bitmap, int x, int y, int height, int width, float angle) :   Image(x,y,height,width, angle) {

    item = new QGraphicsPixmapItem();
    dynamic_cast<QGraphicsPixmapItem*>(item)->setPixmap((QString::fromStdString(bitmap)));
    item->update(x,y,width,height);
}

SquareImage::SquareImage(int x, int y, int height, int width, float angle) : Image(x,y,height,width, angle){

    item = new QGraphicsRectItem(x, y, width, height);
    //item = new QGraphicsRectItem();
    item->update(x,y, height, width);
}

TextBoxImage::TextBoxImage(int x, int y, string txt) : Image(x, y, 0, 0, 0) , text(txt) {

    item = new QGraphicsTextItem(QString::fromStdString(txt));
    item->setX(x); item->setY(y);
    color = BLACK;
    setTextSize(TEXT_SMALL);

}

void TextBoxImage::setText(string txt){

    text = txt;
    dynamic_cast<QGraphicsTextItem*>(item)->setPlainText(QString::fromStdString(txt));
    setTextSize(size);

}

void TextBoxImage::setTextSize(TEXT_SIZE size){

    QGraphicsTextItem *textitem = dynamic_cast<QGraphicsTextItem*>(item);
    QFont font = textitem->font();

    font.setPixelSize(size);
    QFontMetrics metric(font);
    textitem->setFont(font);

    this->size = size;
    setHeight(metric.height());
    setWidth(metric.width(QString::fromStdString(text)));

}
