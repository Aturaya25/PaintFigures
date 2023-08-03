#pragma once
#include "Figure.h"

class Triangle : public Figure
{
public:
	Triangle(const QPoint& startPoint);
	void draw(QPainter& painter) const override;
	void updateParametrs(int count, ...) override;
	bool contains(const QPoint& point) const override;
	void updatePosition(const QPoint& position) override;
	double calculateAngle(const QPoint& start, const QPoint& end) const override;
	QPoint position() override;
	void rotate(double angle) override;
	void updatePointCount();

private:
	QPoint startPoint;
	QPoint secondPoint;
	QPoint thirdPoint;
	int initPointCount;
};