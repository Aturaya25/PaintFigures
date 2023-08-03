#include "Triangle.h"

Triangle::Triangle(const QPoint& startPoint) : startPoint(startPoint)
{
	initPointCount = 1;
    secondPoint = startPoint;
}

void Triangle::draw(QPainter& painter) const
{
    if (initPointCount == 1) {
        painter.drawLine(startPoint, secondPoint);
    }
    else if (initPointCount == 2) {
        painter.drawLine(startPoint, secondPoint);
        painter.drawLine(secondPoint, thirdPoint);
    }
    else if (initPointCount == 3) {
        painter.setBrush(color);
        QPolygon polygon;
        polygon << startPoint << secondPoint << thirdPoint;

        painter.drawPolygon(polygon);
    }
}

void Triangle::updateParametrs(int count, ...)
{
    va_list args;
    va_start(args, count);
    int x = va_arg(args, int);
    int y = va_arg(args, int);
    if (initPointCount == 1) {
        secondPoint = QPoint(x, y);
        thirdPoint = secondPoint;
    }
    else if (initPointCount == 2) {
        thirdPoint = QPoint(x, y);
    }
    va_end(args);
}

bool Triangle::contains(const QPoint& point) const
{
    // Вычисляем барицентрические координаты для заданной точки point
    qreal u = ((secondPoint.y() - thirdPoint.y()) * (point.x() - thirdPoint.x()) +
        (thirdPoint.x() - secondPoint.x()) * (point.y() - thirdPoint.y())) /
        ((secondPoint.y() - thirdPoint.y()) * (startPoint.x() - thirdPoint.x()) +
            (thirdPoint.x() - secondPoint.x()) * (startPoint.y() - thirdPoint.y()));

    qreal v = ((thirdPoint.y() - startPoint.y()) * (point.x() - thirdPoint.x()) +
        (startPoint.x() - thirdPoint.x()) * (point.y() - thirdPoint.y())) /
        ((secondPoint.y() - thirdPoint.y()) * (startPoint.x() - thirdPoint.x()) +
            (thirdPoint.x() - secondPoint.x()) * (startPoint.y() - thirdPoint.y()));

    qreal w = 1.0 - u - v;

    // Проверяем, что условия для барицентрических координат выполняются
    return (u >= 0 && v >= 0 && w >= 0 && u <= 1 && v <= 1 && w <= 1);
}

void Triangle::updatePosition(const QPoint& position)
{
    secondPoint -= startPoint - position - delta;
    thirdPoint -= startPoint - position - delta;
    startPoint = position + delta;
}

double Triangle::calculateAngle(const QPoint& start, const QPoint& end) const
{
    return 0.0;
}

QPoint Triangle::position()
{
    return startPoint;
}

void Triangle::rotate(double angle)
{
}

void Triangle::updatePointCount()
{
    initPointCount++;
}
