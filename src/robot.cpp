#include "robot.h"


Robot::Robot(QGraphicsScene *scene, QGraphicsItem *parent) : ObstacleBase(scene, parent), m_blueBrush(Qt::blue), m_grayBrush(Qt::gray), m_blackBrush(Qt::black)
{
    // m_h = 620*0.19; // 620 = 0.62*1000 // footprint length
    // m_w = 620*(0.09 + 0.05); // foorprint width + wheels
    m_h = 620*0.05; // 620 = 0.62*1000 // footprint length
    m_w = 620*(0.05); // foorprint width + wheels
    
    m_rect.setRect(0,0, m_w, m_h);
    // remember that the coordinates in the sdf are w.r.t the Center of gravity
    rectangle(m_w, m_h);
    this->setTransform(QTransform().translate(m_origin.x(),m_origin.y()).rotate(90).translate(-m_origin.x(),-m_origin.y()),true);
    setPos(m_h + scene->sceneRect().x(),scene->sceneRect().y());

    m_Type = ObstacleBase::ITEM_ROBOT;
    m_Size = ObstacleBase::SIZE_UNKNOWN;
    // m_triangle << QPointF(620*0.025, 0.0) << QPointF(m_w-(0.025*620), 0.0) << QPointF(m_w/2., m_h);
    // m_chassis << QPointF(620*0.025, 0.0) << QPointF(m_w-(0.025*620), 0.0) << QPointF(m_w-(0.025*620), m_h) << QPointF(620*0.025, m_h);
    m_chassis << QPointF(0.0, 0.0) << QPointF(m_w, 0.0) << QPointF(m_w, m_h) << QPointF(0, m_h);
    // m_wheel << QPointF(0.0, 0.0225*620) << QPointF(m_w, 0.0225*620) << QPointF(m_w, 0.0775*620) << QPointF(0.0, 0.0775*620);
    createHandles();
    // m_placeholder = QPointF(m_w/2., 0.05*620.0);
    m_placeholder = QPointF(m_w/2., m_h/2.);
}

QRectF Robot::boundingRect() const
{
    return ObstacleBase::boundingRect();
}


void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawConvexPolygon(m_chassis.data(),4);
    // painter->drawConvexPolygon(m_triangle.data(),3);
    painter->drawEllipse(m_placeholder, 2, 2);
    // QPainterPath path_0;
    // path_0.addPolygon(m_wheel);
    // painter->fillPath(path_0, m_blackBrush);
    QPainterPath path_1;
    path_1.addPolygon(m_chassis);
    painter->fillPath(path_1, m_grayBrush);
    // QPainterPath path_2;
    // path_2.addPolygon(m_triangle);
    // painter->fillPath(path_2, m_blueBrush);
    ObstacleBase::paint(painter,option,widget);
    scene()->update();
}


