#pragma once
#include "Figure.h"

class Triangle : public Figure
{
public:
	Triangle(const QPointF& startPoint);
	void draw(QPainter& painter) const override;
	void updateParametrs(int count, ...) override;
	void updatePointCount();

private:
	QPointF startPoint;
	QPointF secondPoint;
	QPointF thirdPoint;
	int initPointCount;
};