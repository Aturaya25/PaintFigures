#include "square.h"
#include <iostream>
#include <QDebug>

Square::Square(const QPoint& center) : center(center), sideLength(0)
{

}

QRect Square::calculateSquareRect() const
{
    qreal halfSide = sideLength / 2.0;
    QPoint topLeft(center.x() - halfSide, center.y() - halfSide);
    return QRect(topLeft, QSize(sideLength, sideLength));
}

void Square::draw(QPainter& painter) const
{
    QRect squareRect = calculateSquareRect();
    painter.setBrush(color);
    painter.drawRect(squareRect);
}

bool Square::contains(const QPoint& point) const
{
    QRect squareRect = calculateSquareRect();
    return squareRect.contains(point);
}

void Square::updateParametrs(int count, ...)
{
    va_list args;
    va_start(args, count);
    int x = va_arg(args, int);
    int y = va_arg(args, int);
    this->sideLength = qMax(qAbs(x - center.x()), qAbs(y - center.y())) * 2;
    va_end(args);
}

double Square::calculateAngle(const QPoint& start, const QPoint& end) const
{
    // Вычисляем разницу координат между центром и точками начала и конца
    double startX = start.x() - center.x();
    double startY = start.y() - center.y();
    double endX = end.x() - center.x();
    double endY = end.y() - center.y();

    // Вычисляем арктангенс отношения координат
    double startAngle = std::atan2(startY, startX);
    double endAngle = std::atan2(endY, endX);

    // Вычисляем разницу углов, чтобы получить угол поворота
    double angle = endAngle - startAngle;

    return angle;
}

void Square::rotate(double angle)
{
    QRect rect = calculateSquareRect();
    // Вычисляем разницу координат между центром и вершинами квадрата
    double dx = center.x() - this->center.x();
    double dy = center.y() - this->center.y();

    // Поворачиваем вершины квадрата относительно его центра
    double newTopLeftX = dx + (rect.topLeft().x() - center.x()) * std::cos(angle) - (rect.topLeft().y() - center.y()) * std::sin(angle);
    double newTopLeftY = dy + (rect.topLeft().x() - center.x()) * std::sin(angle) + (rect.topLeft().y() - center.y()) * std::cos(angle);
    double newSideLength = sideLength;

    // Обновляем новые координаты вершин квадрата
    rect.topLeft() = QPoint(newTopLeftX, newTopLeftY);
    sideLength = newSideLength;
}

void Square::updatePosition(const QPoint& position)
{
    center = position + delta;
}

QPoint Square::position()
{
    return center;
}

Square::~Square()
{

}
