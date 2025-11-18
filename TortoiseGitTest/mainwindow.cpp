#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::MainWindow)
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeGL()
{
}

void MainWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MainWindow::paintGL()
{
    glClearColor(66./255, 170./255, 255./255, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluPerspective(45.0f, (float)100 / (float)100, 0.1f, 10000.0f);

    gluLookAt(0, 100, 1, 0, 1, 0, 0, 1, 0);

    int a = 10;
    glBegin(GL_QUADS);

        glColor3d(1,0,0);
        glVertex3d(-a,0,a);
        glVertex3d(-a,0,-a);
        glVertex3d(-a,50,-a);
        glVertex3d(-a,50,a);

        glColor3d(0,1,0);
        glVertex3d(-a,0,a);
        glVertex3d(a,0,a);
        glVertex3d(a,50,a);
        glVertex3d(-a,50,a);

        glColor3d(0,0,1);
        glVertex3d(a,0,a);
        glVertex3d(a,0,-a);
        glVertex3d(a,50,-a);
        glVertex3d(a,50,a);

        glColor3d(1,1,0);
        glVertex3d(a,0,-a);
        glVertex3d(-a,0,-a);
        glVertex3d(-a,50,-a);
        glVertex3d(a,50,-a);

        glColor3d(150./255,75./255,0);
        glVertex3d(a,0,a);
        glColor3d(1,75./255,0);
        glVertex3d(a,0,-a);
        glColor3d(150./255,1,0);
        glVertex3d(-a,0,-a);
        glColor3d(150./255,75./255,1);
        glVertex3d(-a,0,a);

        glEnd();
}

