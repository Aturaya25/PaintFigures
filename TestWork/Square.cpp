#include "square.h"
#include <iostream>
#include <QDebug>

Square::Square(const QPointF& center, qreal sideLength) : center(center), sideLength(sideLength)
{

}

QRectF Square::calculateSquareRect() const
{
    qreal halfSide = sideLength / 2.0;
    QPointF topLeft(center.x() - halfSide, center.y() - halfSide);
    return QRectF(topLeft, QSizeF(sideLength, sideLength));
}

void Square::draw(QPainter& painter) const
{
    QRectF squareRect = calculateSquareRect();
    painter.setBrush(Qt::blue);
    painter.drawRect(squareRect);
}

bool Square::contains(const QPoint& point) const
{
    QRectF squareRect = calculateSquareRect();
    // ѕроверка, находитс€ ли точка внутри квадрата
    return squareRect.contains(point);
}

void Square::updateParametrs(int count, ...)
{
    va_list args;
    va_start(args, count);
    qreal parameter = va_arg(args, qreal);
    std::cout << parameter << std::endl;
    this->sideLength = parameter;
}

Square::~Square()
{

}
