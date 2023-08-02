#pragma once
#include "figure.h"

class Circle : public Figure
{
public:
    Circle(const QPointF& startPos);
    void draw(QPainter& painter) const override;
    void updateParametrs(int count, ...) override;

private:
    QPointF startPos;
    qreal radius = 0;
};
