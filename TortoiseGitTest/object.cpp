#include "object.h"

object::object()
{

}

void object::openObj(QString objpath, QString texpath)
{
    FILE *file;
    fopen_s(&file, objpath.toLocal8Bit(), "r");
    if (file == NULL)
    {
        qDebug() << "Impossible to open the file !\n";
        return;
    }
    while (1)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader, 3);
        if (res == EOF)
            break;
        if (strcmp(lineHeader, "v") == 0)
        {
            float x, y, z;
            fscanf(file, "%g %g %g\n", &x, &y, &z);
            this->vertices.push_back({ x, y, z });
        }
        if (strcmp(lineHeader, "vt") == 0)
        {
            float x, y;
            fscanf(file, "%g %g\n", &x, &y);
            this->textures.push_back({ x, y });
        }
        if (strcmp(lineHeader, "vn") == 0)
        {
            float x, y, z;
            fscanf(file, "%g %g %g\n", &x, &y, &z);
            this->normals.push_back({ x, y, z });
        }
        if (strcmp(lineHeader, "f") == 0)
        {
            int vertexIndex[3] = {0,0,0}, textureIndex[3] = { 0,0,0 }, normalIndex[3] = { 0,0,0 };
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &textureIndex[0], &normalIndex[0],
                &vertexIndex[1], &textureIndex[1], &normalIndex[1],
                    &vertexIndex[2], &textureIndex[2], &normalIndex[2]);
            this->vertice_index.push_back(int3(vertexIndex));
            this->texture_index.push_back(int3(textureIndex));
            this->normal_index.push_back(int3(normalIndex));
        }
    }

    this->texture = new QOpenGLTexture(QImage(texpath));
    this->texture->setMinificationFilter(QOpenGLTexture::Linear);
    this->texture->setMagnificationFilter(QOpenGLTexture::Linear);
    this->texture->bind();

    fclose(file);
}

void object::paintObj(double angle)
{
    vec3 size = this->size;
    glPushMatrix();
    glScaled(size.x, size.y, size.z);

    if (this->texture)
    {
    this->texture->bind();
    glEnable(GL_TEXTURE_2D);
    }

    for (int i = 0; i < this->vertice_index.size(); i++)
    {
        glBegin(GL_POLYGON);

        glColor3d(1, 1, 1);

        glNormal3d( this->normals.at(this->normal_index[i].data[0]-1).x(),
                    this->normals.at(this->normal_index[i].data[0]-1).y(),
                    this->normals.at(this->normal_index[i].data[0]-1).z());

        glTexCoord2d(this->textures.at(this->texture_index[i].data[0]-1).x(),
                    -this->textures.at(this->texture_index[i].data[0]-1).y());
        glVertex3d( this->vertices.at(this->vertice_index[i].data[0]-1).x(),
                    this->vertices.at(this->vertice_index[i].data[0]-1).y(),
                    this->vertices.at(this->vertice_index[i].data[0]-1).z());

        glTexCoord2d(this->textures.at(this->texture_index[i].data[1]-1).x(),
                    -this->textures.at(this->texture_index[i].data[1]-1).y());
        glVertex3d( this->vertices.at(this->vertice_index[i].data[1]-1).x(),
                    this->vertices.at(this->vertice_index[i].data[1]-1).y(),
                    this->vertices.at(this->vertice_index[i].data[1]-1).z());

        glTexCoord2d(this->textures.at(this->texture_index[i].data[2]-1).x(),
                    -this->textures.at(this->texture_index[i].data[2]-1).y());
        glVertex3d( this->vertices.at(this->vertice_index[i].data[2]-1).x(),
                    this->vertices.at(this->vertice_index[i].data[2]-1).y(),
                    this->vertices.at(this->vertice_index[i].data[2]-1).z());
        glEnd();
    }
    if (this->texture)
    {
        glDisable(GL_TEXTURE_2D);
        this->texture->release();
    }

    glPopMatrix();
}
