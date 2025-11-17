#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <gl/GL.h>
#include <gl/GLU.h>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
