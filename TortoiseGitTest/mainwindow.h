#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <libs.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    vec3 camPos = {0, 0, 0};
    vec3 camDir = {1, 0, 0};
    bool AppActive = true;

    void keyPressEvent(QKeyEvent * ke);
    void mousePressEvent(QMouseEvent * me);
    void mouseMoveEvent(QMouseEvent * me);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
