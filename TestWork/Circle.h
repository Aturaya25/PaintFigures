#pragma once
#include "figure.h"

class Circle : public Figure
{
public:
    Circle(const QPoint& startPos, QWidget* parent);
    void draw() const override;
    //    void updateParametrs(int count, ...) override;
    void updateShapeParametrs(const QPoint& point) override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    //    double calculateAngle(const QPoint& start, const QPoint& end) const override;
    QPoint center() const override;
    QPoint position() override;
    bool isIntersectSelection(const QRect& rect) const override;

private:
    QPoint startPos;
    int radius = 0;
};
