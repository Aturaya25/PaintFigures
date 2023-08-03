#include "reactangle.h"

Reactangle::Reactangle(const QPoint& startPos) : startPos(startPos)
{
    currentPos = startPos;
}

void Reactangle::draw(QPainter& painter) const
{
    QRect squareRect(startPos, currentPos);
    painter.setBrush(color);
    painter.drawRect(squareRect);
}

void Reactangle::updateParametrs(int count, ...)
{
    va_list args;
    va_start(args, count);
    int x = va_arg(args, int);
    int y = va_arg(args, int);
    currentPos = QPoint(x,y);
    va_end(args);
}

bool Reactangle::contains(const QPoint& point) const
{
    QRect squareRect = QRect(startPos, currentPos);
    return squareRect.contains(point);
}

void Reactangle::updatePosition(const QPoint& position)
{
    currentPos += position - startPos + delta;
    startPos = position + delta;
}

double Reactangle::calculateAngle(const QPoint& start, const QPoint& end) const
{
    return 0.0;
}

QPoint Reactangle::position()
{
    return startPos;
}

void Reactangle::rotate(double angle)
{
}
