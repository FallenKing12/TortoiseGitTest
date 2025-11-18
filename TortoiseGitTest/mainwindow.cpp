#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::MainWindow)
{
    this->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeGL()
{
    colt.openObj("D:/TortoiseGitTest/TortoiseGitTest/objects/colt1911.obj", "D:/TortoiseGitTest/TortoiseGitTest/textures/texture.png");
    colt.size = {0.5, 0.5, 0.5};
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

    gluLookAt(camPos.x, camPos.y, camPos.z, camPos.x + camDir.x, camPos.y + camDir.y, camPos.z + camDir.z, 0, 1, 0);

    if (AppActive)
    {
        QCursor c = cursor();
        if (this->isActiveWindow())
        {
            c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
        }
        c.setShape(Qt::BlankCursor);
        setCursor(c);
    }

    glPushMatrix();
        glTranslated(0, 50, 0);
        colt.paintObj(0);
    glPopMatrix();

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

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    switch (ke->key())
    {
        case (Qt::Key_W):
        camPos = camPos + camDir;
        break;
        case (Qt::Key_S):
        camPos = camPos - camDir;
        break;
        case (Qt::Key_A):
        camPos = camPos - vec3{camDir.x, 0, camDir.z}.rotated({0, 1, 0}, M_PI / 2);
        break;
        case (Qt::Key_D):
        camPos = camPos + vec3{camDir.x, 0, camDir.z}.rotated({0, 1, 0}, M_PI / 2);
        break;

        case (Qt::Key_Space):
        camPos = camPos + vec3{0, 1, 0};
        break;
        case (Qt::Key_Shift):
        camPos = camPos - vec3{0, 1, 0};
        break;

        case (Qt::Key_Escape):
            if (AppActive)
                AppActive = false;
            else
                qApp->quit();
            break;
    }


    update();
}

void MainWindow::mousePressEvent(QMouseEvent *me)
{
    if (!AppActive)
        AppActive = true;

    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *me)
{
    if (AppActive)
    {
        double dx = (me->pos().x() - this->width() / 2) * 0.001;
        double dy = (me->pos().y() - this->height() / 2) * 0.001;

        camDir.rotate({0, 1, 0}, dx);
        camDir.rotate(camDir * (camDir + vec3{0, 1, 0}), dy);
    }

    update();
}

