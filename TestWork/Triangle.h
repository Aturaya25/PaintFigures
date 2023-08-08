#pragma once
#include "Figure.h"

#define TRIANGLETYPE 3

class Triangle : public Figure
{
public:
    Triangle(const QPoint& startPoint, QWidget* parent);
    void draw() const override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    QPoint position() override;
    void updateShapeParametrs(const QPoint& point) override;
    bool isIntersectSelection(const QRect& rect) const override;
    int getType() const override;
    void serialize(QDataStream& out) const override;
    void deserialize(QDataStream& in) override;
    void updatePointCount();


    QPoint center() const override;

private:
    QPoint startPoint;
    QPoint secondPoint;
    QPoint thirdPoint;
    int initPointCount;
};
