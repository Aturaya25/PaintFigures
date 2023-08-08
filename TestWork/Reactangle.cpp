#include "reactangle.h"
Reactangle::Reactangle(const QPoint& startPos, QWidget* parent) :Figure(startPos, parent), startPos(mainPoint)
{
    currentPos = startPos;
}

void Reactangle::draw() const
{
    auto painter = getPainter();
    QRect squareRect(startPos, currentPos);
    painter->setBrush(color);
    if (_angle != 0) {
        painter->translate(squareRect.center());
        painter->rotate(_angle);
        painter->translate(-squareRect.center());
    }
    painter->drawRect(squareRect);
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

QPoint Reactangle::center() const
{
    QLineF diag(currentPos, startPos);
    return diag.center().toPoint();
}

QPoint Reactangle::position()
{
    return startPos;
}

void Reactangle::updateShapeParametrs(const QPoint& point)
{
    currentPos = point;
}

bool Reactangle::isIntersectSelection(const QRect& rect) const
{
    QRect squareRect(startPos, currentPos);
    return rect.intersects(squareRect);
}

int Reactangle::getType() const
{
    return REACTANGLETYPE;
}

void Reactangle::serialize(QDataStream& out) const
{
    out << startPos << currentPos << _angle << selectedColor;
}

void Reactangle::deserialize(QDataStream& in)
{
    in >> startPos >> currentPos >> _angle >> selectedColor;
}
