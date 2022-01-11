#ifndef ObstacleBaseBASE_H
#define ObstacleBaseBASE_H

#include "handle.h"
#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QPen>
#include <QSettings>
#include <QGraphicsItem>
#include <QGraphicsScene>

#define USE_MATH_DEFINES

const std::array<std::array<QPointF, 3>,4> DIRDAT = {{{QPointF(41.436, 35.625), QPointF(61.488, 53.25), QPointF(81.839, 70.875)},
                                                      {QPointF(33.588, 33.588), QPointF(50.205, 50.205), QPointF(66.822, 66.822)},
                                                      {QPointF(45.175, 42.964), QPointF(67.525, 64.220), QPointF(45.175, 42.964)},
                                                      {QPointF(47.499, 41.275), QPointF(70.999, 61.695), QPointF(94.498, 82.115)}}};



class ObstacleBase : public QGraphicsItem
{

private:
    Handle *m_currentHandle;
public:
    QPen m_BlackPen;
    QBrush m_Redbrush;
    QPointF m_origin;
    enum ItemSize {SIZE_95 = 0, SIZE_142 = 1, SIZE_189 = 2, SIZE_UNKNOWN = 3};
    enum ItemType {ITEM_TRIANGLE = 1, ITEM_RECTANGLE = 2, ITEM_PENTAGON = 3, ITEM_HEXAGON = 4, ITEM_GATE = 5, ITEM_ROBOT = 6};
    ItemType m_Type;
    ItemSize m_Size;
    QVector<QPointF> m_Points;
    QRectF m_rect;
    qreal m_w;
    qreal m_h;
    QPointF m_placeholder;

    ObstacleBase(QGraphicsScene* scene = 0, QGraphicsItem* parent = 0);
    virtual QRectF boundingRect() const;
    QPainterPath shape() const; // maybe we are going to change this
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    // no clue what this is all about
    void setId(QString id);
    QString id();
    QPointF computeOffset();



protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void createHandles();
    void update_shape(const QRectF& test);
    void triangle(qreal w, qreal h);
    void rectangle(qreal w, qreal h);
    void pentagon(qreal w, qreal h);
    void hexagon(qreal w, qreal h);
    QList<Handle *> m_handles;
    bool mDrawBoundingRect; // maybe do not need this
    void setDrawBoundingRect(bool draw); // probably do not this either
    void update_shape();
};


#endif // ObstacleBaseBASE_H
