#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "obstaclebase.h"

class Obstacle : public ObstacleBase
{
public:
    Obstacle(ItemSize size,ItemType type, QGraphicsScene *scene, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void get_shape(const float& w, const float& h);

};
#endif // OBSTACLE_H
