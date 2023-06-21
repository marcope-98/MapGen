#include "robot.h"
#include <string>
Robot::Robot(QGraphicsScene *scene, int number, QGraphicsItem *parent) : Base(scene, parent)
{
  // m_h = 620*0.19; // 620 = 0.62*1000 // footprint length
  // m_w = 620*(0.09 + 0.05); // foorprint width + wheels
  m_h = 620 * 0.05; // 620 = 0.62*1000 // footprint length
  m_w = 620 * 0.05; // foorprint width + wheels

  m_rect.setRect(0, 0, m_w, m_h);
  // remember that the coordinates in the sdf are w.r.t the Center of gravity
  rectangle(m_w, m_h);
  this->setTransform(QTransform().translate(m_origin.x(), m_origin.y()).rotate(90).translate(-m_origin.x(), -m_origin.y()), true);
  setPos(m_h + scene->sceneRect().x(), scene->sceneRect().y());

  m_Type = Base::ITEM_ROBOT;
  m_Size = Base::SIZE_UNKNOWN + number;
  m_chassis << QPointF(0.0, 0.0) << QPointF(m_w, 0.0) << QPointF(m_w, m_h) << QPointF(0, m_h);
  createHandles();
  m_placeholder = QPointF(m_w / 2., m_h / 2.);
}

QRectF Robot::boundingRect() const
{
  return Base::boundingRect();
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QFont font;
  font.setPixelSize(21);
  Q_UNUSED(widget);
  Q_UNUSED(option);
  painter->drawConvexPolygon(m_chassis.data(), 4);
  painter->drawEllipse(m_placeholder, 2, 2);

  QPainterPath path_1;
  path_1.addPolygon(m_chassis);
  painter->fillPath(path_1, QBrush(Qt::gray));

  painter->setFont(font);
  painter->drawText(QPoint(10, m_h - 8), std::to_string(this->m_Size - 3).c_str());

  Base::paint(painter, option, widget);
  scene()->update();
}
