#include "obstacle.h"

Obstacle::Obstacle(ItemSize size,ItemType type,QGraphicsScene *scene, QGraphicsItem *parent) : ObstacleBase(scene,parent)
{
    m_Size = size;
    m_Type = type;
    QPointF size_ = DIRDAT[m_Type-1][m_Size];
    m_w = size_.x()*0.62*2.;
    m_h = size_.y()*0.62*2.;
    get_shape(m_w, m_h);
    m_rect.setRect(0.0,0.0,m_w,m_h);
    createHandles();
    setPos(scene->sceneRect().topLeft());
}


void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setRenderHint(QPainter::Antialiasing, true);
    switch (m_Type) {
    case ITEM_TRIANGLE:
        painter->drawConvexPolygon(m_Points.data(), 3);
        break;
    case ITEM_RECTANGLE:
        //painter->drawRect(this->m_rect);
        painter->drawConvexPolygon(m_Points.data(), 4);
        break;
    case ITEM_PENTAGON:
        painter->drawConvexPolygon(m_Points.data(), 5);
        break;
    case ITEM_HEXAGON:
        painter->drawConvexPolygon(m_Points.data(), 6);
        break;
    default:
        break;
    }
    QPainterPath path;
    path.addPolygon(m_Points);
    painter->fillPath(path, m_Redbrush);
    ObstacleBase::paint(painter,option,widget);
    scene()->update();
}

void Obstacle::get_shape(const float &w, const float &h)
{
    switch (m_Type)
    {
        case (ITEM_TRIANGLE):
        triangle(w,h);
        break;
        case (ITEM_RECTANGLE):
        rectangle(w,h);
        break;
        case (ITEM_PENTAGON):
        pentagon(w,h);
        break;
        case (ITEM_HEXAGON):
        hexagon(w,h);
        break;
    case (ITEM_GATE):
    case(ITEM_ROBOT):
        break;
    }
}


QRectF Obstacle::boundingRect() const{
    return ObstacleBase::boundingRect();
}
