#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    //enable the event Filter
    qApp->installEventFilter(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//disable scrollbar (horizontal)
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//disable scrollbar (vertical)
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showEvent(QShowEvent *){
    //setting QGraphicsScene
    scene = new QGraphicsScene(0, 0, 960, 540);
    scene->setBackgroundBrush(QBrush(QImage(":/Background.png")));
    ui->graphicsView->setScene(scene);
    //create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    //setting Size
    GameItem::setGlobalSize(QSizeF(32.0f, 18.0f),size());
    //create ground
    itemList.push_back(new Land(16.0f, 1.5f, 32.0f, 3.0f, QPixmap(":/ground.png").scaled(960,90), world, scene));
    //create brick
    brick_1 = new brick(15.5f, 5.0f, 1.0f, 4.0f, &timer, QPixmap(":/WOOD_1x2").scaled(30, 120), world, scene);
    brick_2 = new brick(18.5f, 5.0f, 1.0f, 4.0f, &timer, QPixmap(":/WOOD_1x2").scaled(30, 120), world, scene);
    brick_3 = new brick(17.0f, 7.5f, 5.3f, 1.0f, &timer, QPixmap(":/WOOD_2x1").scaled(160, 30), world, scene);
    brick_4 = new brick(23.5f, 5.0f, 1.0f, 4.0f, &timer, QPixmap(":/WOOD_1x2").scaled(30, 120), world, scene);
    brick_5 = new brick(26.5f, 5.0f, 1.0f, 4.0f, &timer, QPixmap(":/WOOD_1x2").scaled(30, 120), world, scene);
    brick_6 = new brick(25.0f, 7.5f, 5.3f, 1.0f, &timer, QPixmap(":/WOOD_2x1").scaled(160, 30), world, scene);
    brick_7 = new brick(17.25f, 9.0f, 2.0f, 2.0f, &timer, QPixmap(":/WOOD_2x2").scaled(60, 60), world, scene);
    brick_8 = new brick(25.25f, 9.0f, 2.0f, 2.0f, &timer, QPixmap(":/WOOD_2x2").scaled(60, 60), world, scene);
    brick_9 = new brick(21.00f, 11.0f, 10.0f, 1.0f, &timer, QPixmap(":/WOOD_2x1").scaled(300, 30), world, scene);
    itemList.push_back(brick_1);
    itemList.push_back(brick_2);
    itemList.push_back(brick_3);
    itemList.push_back(brick_4);
    itemList.push_back(brick_5);
    itemList.push_back(brick_6);
    itemList.push_back(brick_7);
    itemList.push_back(brick_8);
    itemList.push_back(brick_9);
    //create enemy
    pig = new Bird(20.75f, 4.0f, 0.9f, &timer, QPixmap(":/PIG.png").scaled(50, 50), world, scene);
    //buttons
    QPushButton *Quit = new QPushButton;
    QPixmap quit_p(":/BTN_QUIT.png");
    Quit->setIcon(quit_p);
    Quit->setIconSize(QSize(50, 50));
    Quit->setFixedSize(50,50);
    Quit->setGeometry(870, 30, 0, 0);
    scene->addWidget(Quit);
    connect(Quit, SIGNAL(clicked()), this, SLOT(close()));

    QPushButton *Restart = new QPushButton;
    QPixmap restart_p(":/BTN_RESTART.png");
    Restart->setIcon(restart_p);
    Restart->setIconSize(QSize(50, 50));
    Restart->setFixedSize(50,50);
    Restart->setGeometry(800, 30, 0, 0);
    scene->addWidget(Restart);
    connect(Restart, SIGNAL(clicked()), this, SLOT(Restart()));
    //timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(this, SIGNAL(quitGame()), this, SLOT(QUITSLOT()));
    timer.start(80/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
        if (mouse_event->button() == Qt::LeftButton){
            click++;
            //Bird 1
            if (click == 5) {
                first_x=mouse_event->x();   first_y=mouse_event->y();
                bird_1= new Bird(1.0f, 6.0f, 1.0f, &timer, QPixmap(":/BIRD_RED.png").scaled(60, 60), world, scene);
                itemList.push_back(bird_1);
            }
            else if (click == 10){
                end_x=mouse_event->x(); end_y=mouse_event->y();
                bird_1->pull(end_x-first_x, end_y-first_y);
            }
            //Bird 2
            else if (click == 15) {
                first_x=mouse_event->x();   first_y=mouse_event->y();
                bird_2= new Bird(1.0f, 6.0f, 1.0f, &timer, QPixmap(":/BIRD_YELLOW.png").scaled(60, 60), world, scene);
                itemList.push_back(bird_2);
            }
            else if (click == 20) {
                end_x=mouse_event->x();   end_y=mouse_event->y();
                bird_2->pull(end_x-first_x, end_y-first_y);
            }
            //Bird 3
            else if (click == 25) {
                first_x=mouse_event->x();   first_y=mouse_event->y();
                bird_3_1= new Bird(1.0f, 6.0f, 0.5f, &timer, QPixmap(":/BIRD_BLUE.png").scaled(30, 30), world, scene);
                itemList.push_back(bird_3_1);
            }
            else if (click == 30) {
                end_x=mouse_event->x();   end_y=mouse_event->y();
                bird_3_1->pull(end_x-first_x, end_y-first_y);
            }
            //Bird 4
            else if (click == 35) {
                first_x=mouse_event->x();   first_y=mouse_event->y();
                bird_4= new Bird(1.0f, 6.0f, 1.0f, &timer, QPixmap(":/BIRD_LANDO.png").scaled(60, 60), world, scene);
                itemList.push_back(bird_4);
            }
            else if (click == 40) {
                end_x=mouse_event->x();   end_y=mouse_event->y();
                bird_4->pull(end_x-first_x, end_y-first_y);
            }
            //Bird 5
            else if (click == 45) {
                first_x=mouse_event->x();   first_y=mouse_event->y();
                bird_5= new Bird(1.0f, 6.0f, 1.0f, &timer, QPixmap(":/BIRD_5.png").scaled(60, 60), world, scene);
                itemList.push_back(bird_5);
            }
            else if (click == 50) {
                end_x=mouse_event->x();   end_y=mouse_event->y();
                bird_5->pull(end_x-first_x, end_y-first_y);
            }
        }
        else if (mouse_event->button() == Qt::RightButton){
            click2++;
            //Bird 2 skill
            if (click2 == 5 && click >= 20)
                bird_2->setLinearVelocity(b2Vec2(50, 1));
            //Bird 3 skill
            else if (click2 == 10 && click >= 30) {
                bird_3_2= new Bird(1.0f, 18.0f, 0.5f, &timer, QPixmap(":/BIRD_BLUE.png").scaled(30, 30), world, scene);
                itemList.push_back(bird_3_2);
                bird_3_2->setLinearVelocity(b2Vec2(22, -10));
                bird_3_3= new Bird(5.0f, 18.0f, 0.5f, &timer, QPixmap(":/BIRD_BLUE.png").scaled(30, 30), world, scene);
                itemList.push_back(bird_3_3);
                bird_3_3->setLinearVelocity(b2Vec2(22, -10));
            }
            //Bird 4 skill
            else if (click2 == 15 && click >= 40)
                bird_4->setLinearVelocity(b2Vec2(5, -30));
            //Bird 5 skill
            else if (click2 == 20 && click >= 50)
                bird_5->setLinearVelocity(b2Vec2(-22, -10));
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *){
    //close event
    emit quitGame();
}

void MainWindow::tick(){
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT(){
    std::cout << "I quit !" << std::endl;
}

void MainWindow::Restart() {
    if (click>=5) delete bird_1;
    if (click>=15) delete bird_2;
    if (click>=25) delete bird_3_1;
    if (click2>=10) delete bird_3_2;
    if (click2>=10) delete bird_3_3;
    if (click>=35) delete bird_4;
    delete brick_1; delete brick_2; delete brick_3; delete brick_4; delete brick_5; delete brick_6; delete brick_7; delete brick_8; delete brick_9;
    delete pig;
    sleep(5);
    click=click2=0;
    brick_1 = new brick(15.5f, 5.0f, 1.0f, 4.0f, &timer, QPixmap(":/WOOD_1x2").scaled(30, 120), world, scene);
    brick_2 = new brick(18.5f, 5.0f, 1.0f, 4.0f, &timer, QPixmap(":/WOOD_1x2").scaled(30, 120), world, scene);
    brick_3 = new brick(16.5f, 7.5f, 4.0f, 1.0f, &timer, QPixmap(":/WOOD_2x1").scaled(160, 30), world, scene);
    brick_4 = new brick(23.5f, 5.0f, 1.0f, 4.0f, &timer, QPixmap(":/WOOD_1x2").scaled(30, 120), world, scene);
    brick_5 = new brick(26.5f, 5.0f, 1.0f, 4.0f, &timer, QPixmap(":/WOOD_1x2").scaled(30, 120), world, scene);
    brick_6 = new brick(24.5f, 7.5f, 4.0f, 1.0f, &timer, QPixmap(":/WOOD_2x1").scaled(160, 30), world, scene);
    brick_7 = new brick(17.25f, 9.0f, 2.0f, 2.0f, &timer, QPixmap(":/WOOD_2x2").scaled(60, 60), world, scene);
    brick_8 = new brick(25.25f, 9.0f, 2.0f, 2.0f, &timer, QPixmap(":/WOOD_2x2").scaled(60, 60), world, scene);
    brick_9 = new brick(20.75f, 11.0f, 9.0f, 1.0f, &timer, QPixmap(":/WOOD_2x1").scaled(300, 30), world, scene);
    itemList.push_back(brick_1);
    itemList.push_back(brick_2);
    itemList.push_back(brick_3);
    itemList.push_back(brick_4);
    itemList.push_back(brick_5);
    itemList.push_back(brick_6);
    itemList.push_back(brick_7);
    itemList.push_back(brick_8);
    itemList.push_back(brick_9);
    pig = new Bird(20.75f, 4.0f, 0.9f, &timer, QPixmap(":/PIG.png").scaled(50, 50), world, scene);
    itemList.push_back(pig);
}
