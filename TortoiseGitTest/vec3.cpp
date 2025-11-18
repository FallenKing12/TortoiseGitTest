#include "vec3.h"

vec3::vec3(double x1, double y1, double z1)
{
    x = x1; y = y1; z = z1;
}

vec3 vec3::operator+(vec3 o)
{
    return vec3(x + o.x, y + o.y, z + o.z);
}

vec3 vec3::operator-(vec3 o)
{
    return (*this) + (o * (-1.));
}

vec3 vec3::operator*(double k)
{
    return vec3(k * x, k * y, k * z);
}

vec3 vec3::operator*(vec3 o)
{
    return vec3(y * o.z - z * o.y,
                z * o.x - x * o.z,
                x * o.y - y * o.x);
}

bool vec3::operator==(vec3 o)
{
    return (x == o.x &&
            y == o.y &&
            z == o.z);
}

bool vec3::operator!=(vec3 o)
{
    return !((*this) == o);
}

double vec3::norma()
{
    return sqrt(x * x + y * y + z * z);
}

void vec3::normalize()
{
    double n = this->norma();
    x /= n; y /= n; z /= n;
}

vec3 vec3::normalized()
{
    double n = this->norma();
    return vec3(x / n, y / n, z / n);
}

double vec3::angle(vec3 a)
{
    return (x * a.x + y * a.y + z * a.z) / (this->norma() * a.norma());
}

void vec3::rotate(vec3 axis, double angle)
{
    *this = (*this).rotated(axis, angle);
}

vec3 vec3::rotated(vec3 axis, double angle)
{
    vec3 normAxis = axis.normalized();

    double c = cos(angle);
    double s = sin(angle);

    vec3 temp = (*this)*normAxis;

    double scale = x * normAxis.x + y * normAxis.y + z * normAxis.z;

    return ((*this) * c + temp * s + normAxis * scale * (1 - c));
}
