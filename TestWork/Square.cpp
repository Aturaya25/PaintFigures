#include "square.h"
#include <iostream>
#include <QDebug>

Square::Square(const QPoint& center) :Figure(center), _center(mainPoint), sideLength(0)
{

}

Square::Square(const QPoint& center, QWidget* parent) : Figure(center, parent), _center(mainPoint), sideLength(0)
{

}

QRect Square::calculateSquareRect() const
{
    qreal halfSide = sideLength / 2.0;
    QPoint topLeft(_center.x() - halfSide, _center.y() - halfSide);
    return QRect(topLeft, QSize(sideLength, sideLength));
}

void Square::draw() const
{
    auto painter = getPainter();
    QRect squareRect = calculateSquareRect();
    if (_angle != 0) {
        painter->translate(squareRect.center());
        painter->rotate(_angle);
        painter->translate(-squareRect.center());
    }
    painter->setBrush(color);
    painter->drawRect(squareRect);
}

bool Square::contains(const QPoint& point) const
{
    QRect squareRect = calculateSquareRect();
    return squareRect.contains(point);
}

QPoint Square::center() const
{
    return _center;
}

void Square::updateShapeParametrs(const QPoint& point)
{
    this->sideLength = qMax(qAbs(point.x() - _center.x()), qAbs(point.y() - _center.y())) * 2;
}

bool Square::isIntersectSelection(const QRect& rect) const
{
    QRect squareRect = calculateSquareRect();
    return rect.intersects(squareRect);
}

void Square::updatePosition(const QPoint& position)
{
    _center = position + delta;
}

QPoint Square::position()
{
    return _center;
}

Square::~Square()
{

}
