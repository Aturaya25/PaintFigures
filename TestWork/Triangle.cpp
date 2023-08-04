#include "Triangle.h"

Triangle::Triangle(const QPoint& startPoint, QWidget* parent) :Figure(startPoint, parent), startPoint(mainPoint)
{
    initPointCount = 1;
    secondPoint = startPoint;
}

void Triangle::draw() const
{
    auto painter = getPainter();
    if (initPointCount == 1) {
        painter->drawLine(startPoint, secondPoint);
    }
    else if (initPointCount == 2) {
        painter->drawLine(startPoint, secondPoint);
        painter->drawLine(secondPoint, thirdPoint);
    }
    else if (initPointCount == 3) {
        painter->setBrush(color);
        QPolygon polygon;
        polygon << startPoint << secondPoint << thirdPoint;
        if (_angle != 0) {
            painter->translate(this->center());
            painter->rotate(_angle);
            painter->translate(-this->center());
        }

        painter->drawPolygon(polygon);
    }
}


bool Triangle::contains(const QPoint& point) const
{
    double x0 = point.x();
    double y0 = point.y();
    double x1 = startPoint.x();
    double y1 = startPoint.y();
    double x2 = secondPoint.x();
    double y2 = secondPoint.y();
    double x3 = thirdPoint.x();
    double y3 = thirdPoint.y();
    double s1 = (x1 - x0) * (y2 - y1) - (x2 - x1) * (y1 - y0);
    double s2 = (x2 - x0) * (y3 - y2) - (x3 - x2) * (y2 - y0);
    double s3 = (x3 - x0) * (y1 - y3) - (x1 - x3) * (y3 - y0);
    return (s1 < 0 && s2 < 0 && s3 < 0) || (s1 >= 0 && s2 >= 0 && s3 >= 0);
}

void Triangle::updatePosition(const QPoint& position)
{
    secondPoint -= startPoint - position - delta;
    thirdPoint -= startPoint - position - delta;
    startPoint = position + delta;
}

QPoint Triangle::center() const {
    QPointF _center;

    QLineF l1(startPoint, secondPoint);
    QLineF l2(secondPoint, thirdPoint);
    QLineF l3(thirdPoint, startPoint);

    QLineF m1(startPoint, l2.center());
    QLineF m2(secondPoint, l3.center());


    m1.intersect(m2, &_center);
    return _center.toPoint();
}

QPoint Triangle::position()
{
    return startPoint;
}

void Triangle::updateShapeParametrs(const QPoint& point)
{
    if (initPointCount == 1) {
        secondPoint = point;
        thirdPoint = secondPoint;
    }
    else if (initPointCount == 2) {
        thirdPoint = point;
    }
}

bool Triangle::isIntersectSelection(const QRect& rect) const
{
    auto c = center();
    bool angleInCircle = contains(rect.topLeft()) || contains(rect.topRight()) || contains(rect.bottomLeft()) || contains(rect.bottomRight());
    bool circleCenterInRect = rect.contains(c);
    return angleInCircle || circleCenterInRect || rect.contains(startPoint) || rect.contains(secondPoint) || rect.contains(thirdPoint);
}

void Triangle::updatePointCount()
{
    initPointCount++;
}