#ifndef BRICK_H
#define BRICK_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BRICK_DENSITY 10.0f
#define BRICK_FRICTION 0.2f
#define BRICK_RESTITUTION 0.5f

class brick : public GameItem{
public:
    brick(float x, float y, float width, float height, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BRICK_H
