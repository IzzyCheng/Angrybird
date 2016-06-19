#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <brick.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    int first_x, first_y, end_x, end_y, click=0, click2=0;
signals:
    void quitGame();

private slots:
    void tick();
    void QUITSLOT();
    void Restart();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    Bird *bird_1, *bird_2, *bird_3_1, *bird_3_2, *bird_3_3, *bird_4, *bird_5, *pig;
    brick *brick_1, *brick_2, *brick_3, *brick_4, *brick_5, *brick_6, *brick_7, *brick_8, *brick_9;
};

#endif // MAINWINDOW_H
