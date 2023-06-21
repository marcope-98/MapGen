#ifndef ROBOT_H
#define ROBOT_H
#include "Base.h"

class Robot : public Base
{
private:
  qreal            m_w;
  qreal            m_h;
  QVector<QPointF> m_chassis;

public:
  int robot_number = 1;

  Robot(QGraphicsScene *scene, int number, QGraphicsItem *parent = 0);
  QRectF boundingRect() const;
  void   paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // ROBOT_H
