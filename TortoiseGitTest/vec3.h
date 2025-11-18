#ifndef VEC3_H
#define VEC3_H

#include <math.h>

struct vec3
{
    double x, y, z;
    vec3(double x1 = 0, double y1 = 0, double z1 = 0);

    vec3 operator+(vec3 o);
    vec3 operator-(vec3 o);
    vec3 operator*(double k);
    vec3 operator*(vec3 o);

    bool operator==(vec3 o);
    bool operator!=(vec3 o);

    double norma();
    void normalize();
    vec3 normalized();
    double angle(vec3 a);
    void rotate(vec3 axis, double angle);
    vec3 rotated(vec3 axis, double angle);
};

#endif // VEC3_H
