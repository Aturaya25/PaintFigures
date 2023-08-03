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
    // ��������� ������� ��������� ����� ������� � ������� ������ � �����
    double startX = start.x() - center.x();
    double startY = start.y() - center.y();
    double endX = end.x() - center.x();
    double endY = end.y() - center.y();

    // ��������� ���������� ��������� ���������
    double startAngle = std::atan2(startY, startX);
    double endAngle = std::atan2(endY, endX);

    // ��������� ������� �����, ����� �������� ���� ��������
    double angle = endAngle - startAngle;

    return angle;
}

void Square::rotate(double angle)
{
    QRect rect = calculateSquareRect();
    // ��������� ������� ��������� ����� ������� � ��������� ��������
    double dx = center.x() - this->center.x();
    double dy = center.y() - this->center.y();

    // ������������ ������� �������� ������������ ��� ������
    double newTopLeftX = dx + (rect.topLeft().x() - center.x()) * std::cos(angle) - (rect.topLeft().y() - center.y()) * std::sin(angle);
    double newTopLeftY = dy + (rect.topLeft().x() - center.x()) * std::sin(angle) + (rect.topLeft().y() - center.y()) * std::cos(angle);
    double newSideLength = sideLength;

    // ��������� ����� ���������� ������ ��������
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
