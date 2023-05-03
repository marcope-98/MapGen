#ifndef ROBOT_H
#define ROBOT_H
#include "obstaclebase.h"

class Robot : public ObstacleBase
{
private:
    qreal m_w;
    qreal m_h;
    QBrush m_blueBrush;
    QBrush m_grayBrush;
    QBrush m_blackBrush;
    QVector<QPointF> m_triangle;
    QVector<QPointF> m_chassis;
    QVector<QPointF> m_wheel;

public:
    Robot(QGraphicsScene *scene, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // ROBOT_H
