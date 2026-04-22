#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

class Vector3f {

public:
    Vector3f();
    Vector3f(float x, float y, float z);
    ~Vector3f();

    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);

    float getX();
    float getY();
    float getZ();

    void scale(float scalingFactor);
    void add(Vector3f& other);
    void sub(Vector3f& other);

    float getLength();
    void normalise();

private:
    float x;
    float y;
    float z;
};

#endif