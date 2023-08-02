#include "Circle.h"

Circle::Circle(const QPointF& startPos): startPos(startPos)
{
}

void Circle::draw(QPainter& painter) const
{
    painter.setBrush(Qt::red);
    if (radius > 0) {
        painter.drawEllipse(startPos, radius, radius);
    }
}

void Circle::updateParametrs(int count, ...)
{
    va_list args;
    va_start(args, count);
    qreal x = va_arg(args, qreal);
    qreal y = va_arg(args, qreal);
    QPointF currentPos = { x,y };
    radius = QLineF(startPos, currentPos).length();
}
