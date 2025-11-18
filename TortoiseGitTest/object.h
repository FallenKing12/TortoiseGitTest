#ifndef OBJECT_H
#define OBJECT_H

#include <libs.h>

struct int3 // 3intVector
{
    int data[3];
    int3()
    {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
    }
    int3(int ints[3])
    {
        data[0] = ints[0]; data[1] = ints[1]; data[2] = ints[2];
    }
};

class object
{
public:
    object();
    vec3 size;

    QVector<QVector3D> vertices, normals;
    QVector<QPointF> textures;
    QVector<int3> vertice_index, normal_index, texture_index;

    QOpenGLTexture *texture;

    void openObj(QString objpath, QString texpath);
    void paintObj(double angle);

    bool operator==(const object & other)
    {
        return (vertices == other.vertices);
    }
};

#endif // OBJECT_H
