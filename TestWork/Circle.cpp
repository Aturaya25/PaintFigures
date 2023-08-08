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
    return angleInCircle || circleCenterInRect || ppp.intersects(rect);
}

int Circle::getType() const
{
    return CIRCLETYPE;
}

void Circle::serialize(QDataStream& out) const
{
    out << startPos << radius << selectedColor;
}

void Circle::deserialize(QDataStream& in)
{
    in >> startPos >> radius >> selectedColor;
}