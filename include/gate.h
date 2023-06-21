#ifndef GATE_H
#define GATE_H
#include "Base.h"
#include "misc.h"

class Gate : public Base
{
private:
  qreal  m_w;
  qreal  m_h;
  QBrush m_greenBrush;

public:
  Gate(QGraphicsScene *scene, QGraphicsItem *parent = 0);
  QRectF boundingRect() const;
  void   paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  void   mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GATE_H
