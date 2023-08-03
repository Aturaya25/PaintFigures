#pragma once
#include "figure.h"

class Circle : public Figure
{
public:
    Circle(const QPoint& startPos);
    void draw(QPainter& painter) const override;
    void updateParametrs(int count, ...) override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    double calculateAngle(const QPoint& start, const QPoint& end) const override;
    void rotate(double angle) override;
    QPoint position() override;

private:
    QPoint startPos;
    int radius = 0;
};
