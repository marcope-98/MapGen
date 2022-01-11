#ifndef HANDLE_H
#define HANDLE_H
#include <QRectF>
#include <QPainter>

class Handle
{
public:
    enum HandleShape {HANDLE_SHAPE_CIRCLE, HANDLE_SHAPE_NONE};

    // prolly need this:
    enum HandleType {HANDLE_TYPE_TOPLEFT, HANDLE_TYPE_TOP, HANDLE_TYPE_TOPRIGHT, HANDLE_TYPE_LEFT, HANDLE_TYPE_RIGHT , HANDLE_TYPE_BOTTOMLEFT, HANDLE_TYPE_BOTTOM, HANDLE_TYPE_BOTTOMRIGHT, HANDLE_TYPE_ROTATE,HANDLE_TYPE_CTRL};

    // constructor
    Handle(QPointF pos,int size ,HandleShape shape ,HandleType type);

    //setters:
    void setShape(HandleShape shape);
    void setType(HandleType type);
    void setSize(int size);
    void setPos(QPointF pos);

    //getters:
    HandleShape shape();
    HandleType type();
    QPointF pos();
    QRectF boundingRect() const;
    int size();

private:
    QRectF mRect;
    QPointF mPos;
    HandleType mType;
    HandleShape mShape;
    int mSize;
};

#endif // HANDLE_H
