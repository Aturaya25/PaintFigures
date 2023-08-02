#include "reactangle.h"

Reactangle::Reactangle(const QPointF& startPos) : startPos(startPos)
{
    currentPos = startPos;
}

void Reactangle::draw(QPainter& painter) const
{
    QRectF squareRect(startPos, currentPos);
    painter.setBrush(Qt::yellow);
    painter.drawRect(squareRect);
}

void Reactangle::updateParametrs(int count, ...)
{
    va_list args;
    va_start(args, count);
    qreal x = va_arg(args, qreal);
    qreal y = va_arg(args, qreal);
    currentPos = QPointF(x,y);
}