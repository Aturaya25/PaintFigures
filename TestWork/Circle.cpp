#include "Circle.h"
#include "circle.h"

Circle::Circle(const QPoint& startPos, QWidget* parent) : Figure(startPos, parent), startPos(mainPoint)
{
}

void Circle::draw() const
{
    auto painter = getPainter();
    painter->setBrush(color);
    if (radius > 0) {
        painter->drawEllipse(startPos, radius, radius);
    }
}

//void Circle::updateParametrs(int count, ...)
//{
//    va_list args;
//    va_start(args, count);
//    if (count == 1){
//        va_end(args);
//        return;
//    }
//    int x = va_arg(args, int);
//    int y = va_arg(args, int);
//    QPoint currentPos = { x,y };
//    radius = QLineF(startPos, currentPos).length();
//    va_end(args);
//}

void Circle::updateShapeParametrs(const QPoint& point)
{
    radius = QLineF(startPos, point).length();
}

bool Circle::contains(const QPoint& point) const
{
    int distance = std::hypot(startPos.x() - point.x(), startPos.y() - point.y());
    return distance <= radius;
}

void Circle::updatePosition(const QPoint& position)
{
    startPos = position + delta;
}

QPoint Circle::center() const
{
    return startPos;
}


QPoint Circle::position()
{
    return startPos;
}

bool Circle::isIntersectSelection(const QRect& rect) const
{
    auto c = center();
    bool angleInCircle = contains(rect.topLeft()) || contains(rect.topRight()) || contains(rect.bottomLeft()) || contains(rect.bottomRight());
    bool circleCenterInRect = rect.contains(c);


    QPainterPath ppp;
    ppp.addEllipse(startPos, radius, radius);

    ppp.intersects(rect);


    return angleInCircle || circleCenterInRect || ppp.intersects(rect);;
}