#include "Triangle.h"

Triangle::Triangle(const QPointF& startPoint) : startPoint(startPoint)
{
	initPointCount = 1;
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
		painter.setBrush(Qt::green);
		QPolygonF polygon;
		polygon << startPoint << secondPoint << thirdPoint;
		painter.drawPolygon(polygon);
	}
}

void Triangle::updateParametrs(int count, ...)
{
	va_list args;
	va_start(args, count);
	qreal x = va_arg(args, qreal);
	qreal y = va_arg(args, qreal);
	if (initPointCount == 1) {
		secondPoint = QPointF(x, y);
	}
	else {
		thirdPoint = QPointF(x, y);
	}
}

void Triangle::updatePointCount()
{
	initPointCount++;
}

