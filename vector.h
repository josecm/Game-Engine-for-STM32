#ifndef VECTOR_H
#define VECTOR_H
#include <QDebug>
#include <cmath>
#include <iostream>

using namespace std;

class Vector
{

    float x;
    float y;
    float angle;
    float length;

    void updateCart();
    void updatePolar();

public:

    Vector(float x = 1.0, float y = 0.0);

    float getLength() { return length; }
    float getAngle() { return angle; }
    float getX() { return x; }
    float getY() { return y; }

    void setX(float);
    void setY(float);
    void setAngle(float);
    void setLength(float);

    Vector& operator+=(const Vector&);
    Vector& operator-=(const Vector&);
    Vector& operator*=(float);
    Vector& operator/=(float);

    Vector operator+(const Vector&);
    Vector operator-(const Vector&);
    Vector operator*(float);
    Vector operator/(float);

    void rotate(float);
    void stretch(float);

    void reverse();
    void reverseX();
    void reverseY();

    bool operator==(const Vector&);
    bool operator!=(const Vector&);

    float dotProduct(const Vector&);
    void normalize();

    void print();
};

#endif // VECTOR_H
