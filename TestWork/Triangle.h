#pragma once
#include "Figure.h"

class Triangle : public Figure
{
public:
    Triangle(const QPoint& startPoint, QWidget* parent);
    void draw() const override;
    //    void updateParametrs(int count, ...) override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    QPoint position() override;
    void updateShapeParametrs(const QPoint& point) override;
    bool isIntersectSelection(const QRect& rect) const override;
    void updatePointCount();


    QPoint center() const override;

private:
    QPoint startPoint;
    QPoint secondPoint;
    QPoint thirdPoint;
    int initPointCount;
};
