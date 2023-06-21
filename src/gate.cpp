#include "gate.h"

Gate::Gate(QGraphicsScene *scene, QGraphicsItem *parent) : Base(scene, parent), m_greenBrush(Qt::green)
{
  m_w = 620 * 0.1; // 620 = 0.62*1000
  m_h = 620 * 0.2;
  m_rect.setRect(0, 0, m_w, m_h);
  // remember that the coordinates in the sdf are w.r.t the Center of gravity
  rectangle(m_w, m_h);
  setPos(scene->sceneRect().topLeft());
  m_Type   = Base::ITEM_GATE;
  m_Size   = Base::SIZE_UNKNOWN;
  m_origin = this->m_rect.center();
  this->setTransformOriginPoint(m_origin);
}

QRectF Gate::boundingRect() const
{
  return QRectF(0, 0, m_w, m_h);
}

void Gate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(widget);
  Q_UNUSED(option);
  painter->drawConvexPolygon(m_Points.data(), 4);
  QPainterPath path;
  path.addPolygon(m_Points);
  painter->fillPath(path, m_greenBrush);
  scene()->update();
}

void Gate::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QRectF rect    = scene()->sceneRect();
  qreal  angle_1 = rangeSymm(atan2(rect.height(), rect.width()));
  qreal  angle_2 = rangeSymm(-angle_1);
  qreal  angle_3 = rangeSymm(angle_1 + M_PI);
  qreal  angle_4 = rangeSymm(angle_2 + M_PI);

  QPointF rect_center = rect.center();
  QPointF pos_center  = mapToParent(m_origin);
  QPointF pos_wrt_center(pos_center.x() - rect_center.x(), pos_center.y() - rect_center.y());
  qreal   angle = rangeSymm(atan2(pos_wrt_center.y(), pos_wrt_center.x()));
  if (angle < angle_4 && angle >= angle_1)
  {
    setRotation(90);
    setY(rect.bottom());
  }
  else if (angle < angle_1 && angle >= angle_2)
  {
    setRotation(0);
    setX(rect.right());
  }
  else if (angle < angle_2 && angle >= angle_3)
  {
    setRotation(-270);
    setY(rect.top() - m_w);
  }
  else
  {
    setRotation(180);
    setX(rect.left());
  }

  Base::mouseReleaseEvent(event);
}
