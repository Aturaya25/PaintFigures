#include "Circle.h"

Circle::Circle(const QPoint& startPos): startPos(startPos)
{
}

void Circle::draw(QPainter& painter) const
{
    painter.setBrush(color);
    if (radius > 0) {
        painter.drawEllipse(startPos, radius, radius);
    }
}

void Circle::updateParametrs(int count, ...)
{
    va_list args;
    va_start(args, count);
    int x = va_arg(args, int);
    int y = va_arg(args, int);
    QPoint currentPos = { x,y };
    radius = QLineF(startPos, currentPos).length();
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

double Circle::calculateAngle(const QPoint& start, const QPoint& end) const
{
    return 0.0;
}

void Circle::rotate(double angle)
{
}

QPoint Circle::position()
{
    return startPos;
}
