#include "square.h"
#include <iostream>
#include <QDebug>

Square::Square(const QPointF& center, qreal sideLength) : center(center), sideLength(sideLength)
{

}

void Square::draw(QPainter& painter) const
{
    qreal halfSide = sideLength / 2.0;
    QPointF topLeft(center.x() - halfSide, center.y() - halfSide);
    QRectF squareRect(topLeft, QSizeF(sideLength, sideLength));

    //painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setPen(Qt::black);
    painter.setBrush(Qt::blue);
    painter.drawRect(squareRect);
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
