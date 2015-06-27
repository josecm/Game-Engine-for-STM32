#include "vector.h"

Vector::Vector(float x, float y)
{
    this->x = x;
    this->y = y;

    updatePolar();
}

void Vector::setX(float x){

    this->x = x;
    updatePolar();
}

void Vector::setY(float y){

    this->y = y;
    updatePolar();
}

void Vector::setAngle(float angle){
    this->angle = angle;
    updateCart();
}

void Vector::setLength(float length){
    this->length = length;
    updateCart();
}

void Vector::updateCart() {

    x = length * cos(angle/360.0 * 2.0 * M_PI);
    y = length * sin(angle/360.0 * 2.0 * M_PI);

}

void Vector::updatePolar() {

    angle = atan2(y,x) * 360.0 /(2*M_PI);
    length = sqrt(x * x + y * y);

    while(this->angle > 360.0)
        this->angle -= 360.0;

    while(this->angle < 0.0)
        this->angle += 360.0;


}

Vector& Vector::operator+=(const Vector &v2){

    this->x += v2.x;
    this->y += v2.y;

    updatePolar();

    return *this;

}

Vector& Vector::operator-=(const Vector &v2){

    this->x -= v2.x;
    this->y -= v2.y;

    updatePolar();

    return *this;

}

Vector& Vector::operator*=(float f){

    length *= fabs(f);

    if(f < 0.0){
        angle += 180.0;
        while(angle > 360.0)
            angle -= 360.0;
    }

    updateCart();

    return *this;

}

Vector& Vector::operator/=(float f){

    length /= fabs(f);

    if(f < 0.0){
        angle += 180.0;
        while(angle > 360.0)
            angle -= 360.0;
    }

    updateCart();

    return *this;

}

Vector Vector::operator+(const Vector &v2){

    Vector temp(*this);

    temp.x = this->x + v2.x;
    temp.y = this->y + v2.y;

    temp.updatePolar();

    return temp;

}

Vector Vector::operator-(const Vector &v2){

    Vector temp(*this);

    temp.x = this->x - v2.x;
    temp.y = this->y - v2.y;

    temp.updatePolar();

    return temp;

}

Vector Vector::operator*(float f){

    Vector temp(*this);

    temp.length *= fabs(f);

    if(f < 0.0){
        temp.angle += 180.0;
        while(temp.angle > 360.0)
            temp.angle -= 360.0;
    }

    temp.updateCart();

    return temp;

}

Vector Vector::operator/(float f){

    Vector temp(*this);

    temp.length /= fabs(f);

    if(f < 0.0){
        temp.angle += 180.0;
        while(temp.angle > 360.0)
            temp.angle -= 360.0;
    }

    temp.updateCart();

    return temp;

}

bool Vector::operator==(const Vector &v2){

    if(this->x == v2.x && this->y == v2.y)
        return true;

    return false;

}

bool Vector::operator!=(const Vector &v2){

    if(this->x == v2.x && this->y == v2.y)
        return false;

    return true;

}

float Vector::dotProduct(const Vector &v2){

    return (this->x * v2.x) + (this->y * v2.y);

}

void Vector::normalize(){

    this->x /= this->length;
    this->y /= this->length;

    updatePolar();

}

void Vector::rotate(float angle){

    this->angle += angle;

    while(this->angle > 360.0)
        this->angle -= 360.0;

    while(this->angle < 0.0)
        this->angle += 360.0;

    updateCart();

}

void Vector::stretch(float value){

    this->length +=  value;

    updateCart();
}

void Vector::reverse(){

    y = -y;
    x = -x;

    updatePolar();

}

void Vector::reverseX(){

    x = -x;

    updatePolar();

}

void Vector::reverseY(){

    y = -y;

    updatePolar();
}

void Vector::print(){

    cout << "x: " << x << "; y: " << y << endl;
    cout << "angle: " << angle << "; leng: " << length << endl;
}
