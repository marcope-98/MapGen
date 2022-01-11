#include "obstaclebase.h"

ObstacleBase::ObstacleBase(QGraphicsScene *scene, QGraphicsItem *parent) : QGraphicsItem(parent),m_currentHandle(0),m_BlackPen(Qt::black),m_Redbrush(Qt::red)
{

    m_BlackPen.setWidth(5);
    m_BlackPen.setJoinStyle(Qt::RoundJoin);
    this->mDrawBoundingRect = true;
    this->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    if(scene) {
        scene->addItem(this);
    }

}

void ObstacleBase::setDrawBoundingRect(bool draw) {
    this->mDrawBoundingRect = draw;
}

QRectF ObstacleBase::boundingRect() const {
    QSettings settings;
    //Adjust bounding rectangle to include the handles so clicking them is detected.
    int size = settings.value("drawing/hanleSize",10).toInt();
    return this->m_rect.adjusted(-size/2,-size/2 - 50,size/2,size/2);
}
QPainterPath ObstacleBase::shape() const {
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    if(this->isSelected()) {
        foreach (Handle *handle, m_handles) {
            switch (handle->shape()) {
            case Handle::HANDLE_SHAPE_CIRCLE:
                path.addRect(handle->boundingRect());
                break;
            case Handle::HANDLE_SHAPE_NONE:
                break;
            }
        }
    }
    path.addRect(this->m_rect);
    return path;
}
void ObstacleBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //If the item is selected draw selection rectangle and handles.
    if(this->isSelected()) {
        if(this->mDrawBoundingRect) {
            //Draw Selection Triangle.
            QPen pen(Qt::green);
            painter->setPen(pen);
            painter->drawRect(this->m_rect);
        }
        //Drawing the handles.
        QPointF p1;
        QPointF p2;
        foreach (Handle *handle, m_handles) {
            if(handle->type() == Handle::HANDLE_TYPE_ROTATE) {
                p1 = handle->pos();
            }
            if(handle->type() == Handle::HANDLE_TYPE_TOP) {
                p2 = handle->pos();
            }
                switch (handle->shape()) {
                case Handle::HANDLE_SHAPE_CIRCLE:
                    painter->drawEllipse(handle->boundingRect());
                    break;
                case Handle::HANDLE_SHAPE_NONE:
                    break;
                }
            }
        painter->drawLine(p1,p2);
        painter->drawPoint(this->m_origin);
    }
}
void ObstacleBase::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
    if(event->buttons() == Qt::LeftButton) {
        //Detect which handle is clicked.
        foreach (Handle *handle, m_handles) {
            if(handle->boundingRect().contains(event->pos())) {
                this->m_currentHandle = handle;
            }
        }
    }
}


void ObstacleBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //Left mouse button is down.
    //TODO: Add grid support.

    if(event->buttons() == Qt::LeftButton && m_currentHandle) {
        switch (m_currentHandle->type()) {
        case Handle::HANDLE_TYPE_ROTATE:
            //Setting the origin point.
            this->setTransform(QTransform().translate(m_origin.x(),m_origin.y()).rotate(-QLineF(event->scenePos(),mapToScene(m_origin)).angle() + QLineF(event->lastScenePos(),mapToScene(m_origin)).angle()).translate(-m_origin.x(),-m_origin.y()),true);
            break;
        case Handle::HANDLE_TYPE_CTRL:
            m_currentHandle->setPos(event->pos());
            break;
        default:
            QGraphicsItem::mouseMoveEvent(event);
            break;
        }
        //Update handle positions.
        QPointF top(m_rect.left()+m_rect.width()/2,m_rect.top());
        QPointF rotate(top.x(),top.y()-50);
        foreach (Handle *handle, m_handles) {
            if (handle->type()==Handle::HANDLE_TYPE_ROTATE)
            {
                handle->setPos(rotate);
            }
        }
    } else {
        QGraphicsItem::mouseMoveEvent(event);

    }
}

QPointF ObstacleBase::computeOffset()
{
    QPolygonF abs_rect = mapToParent(m_rect);
    QRectF test(0,0, abs_rect.boundingRect().width(), abs_rect.boundingRect().height());
    return QPointF(test.width()/2., test.height()/2.);
}

void ObstacleBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
    QRectF scene_rect = scene()->sceneRect();
    QPointF offset = computeOffset();
    QRectF rect(scene_rect.left() + offset.x(), scene_rect.top() + offset.y(), scene_rect.width()-2.*offset.x(), scene_rect.height()-2.*offset.y());

    QPointF newPos = mapToParent(m_rect.center());
    if(!rect.contains(newPos))
    {
        qreal delta_x = newPos.x() - qMin(rect.right(), qMax(newPos.x(), rect.left()));
        qreal delta_y = newPos.y() - qMin(rect.bottom(), qMax(newPos.y(), rect.top()));
        setPos(pos()  - QPointF(delta_x,delta_y));
    }


    //Reset handles states.
    this->m_currentHandle = 0;
}

QVariant ObstacleBase::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}

void ObstacleBase::createHandles() {
    QSettings settings;
    int size = settings.value("drawing/hanleSize",10).toInt();
    //Resizing rectangle.
    m_origin = this->m_rect.center();
    QPointF left(m_rect.left(),m_rect.top() + m_rect.height()/2);
    QPointF right(m_rect.right(),m_rect.top() + m_rect.height()/2);
    QPointF top(m_rect.left()+m_rect.width()/2,m_rect.top());
    QPointF bottom(m_rect.left()+m_rect.width()/2,m_rect.bottom());
    QPointF rotate(top.x(),top.y()-50);

    m_handles << new Handle(top,                  size, Handle::HANDLE_SHAPE_NONE,   Handle::HANDLE_TYPE_TOP);
    m_handles << new Handle(rotate,               size, Handle::HANDLE_SHAPE_CIRCLE, Handle::HANDLE_TYPE_ROTATE);
}


void ObstacleBase::triangle(qreal w, qreal h)
{
    m_Points << QPointF(0.f, h)
             << QPointF(w , h)
             << QPointF(w/2.f, 0.f);
}

void ObstacleBase::rectangle(qreal w, qreal h)
{
    m_Points << QPointF(0.f,0.f)
             << QPointF(0.f,h)
             << QPointF(w, h)
             << QPointF(w, 0.f);
}

void ObstacleBase::pentagon(qreal w, qreal h)
{
    float t_s1 = sinf(M_PI*0.4f);
    float t_s2 = sinf(M_PI*0.8f);
    float t_c1 = cosf(M_PI*0.4f);
    float t_radius = w/(2.f*t_s1);
    m_Points << QPointF(w/2.f,0.0)
             << QPointF(w, t_radius - t_radius*t_c1)
             << QPointF(w/2.f + t_radius*t_s2, h)
             << QPointF(w/2.f - t_radius*t_s2, h)
             << QPointF(0.0, t_radius - t_radius*t_c1);
}

void ObstacleBase::hexagon(qreal w, qreal h)
{
    float t_radius2 = w/2.f;
    float t_c60 = t_radius2*cos(M_PI/3.f);
    m_Points << QPointF(0.0, h/2.f)
             << QPointF(t_radius2 - t_c60, 0.0)
             << QPointF(t_radius2 + t_c60, 0.0)
             << QPointF(w, h/2.f)
             << QPointF(t_radius2 + t_c60, h)
             << QPointF(t_radius2 - t_c60, h);
}

void ObstacleBase::update_shape(const QRectF& test)
{
    m_Points.clear();
    switch(m_Type)
    {
    case ITEM_TRIANGLE:
        triangle(test.width(),test.height());
        break;
    case ITEM_RECTANGLE:
        rectangle(test.width(), test.height());
        break;
    case ITEM_PENTAGON:
        pentagon(test.width(), test.height());
        break;
    case ITEM_HEXAGON:
        hexagon(test.width(), test.height());
        break;
    case ITEM_GATE:
        rectangle(test.width(), test.height());
        break;
    case ITEM_ROBOT:
        break;
    }
}
