#ifndef CIRCLE_H
#define CIRCLE_H
#include <cmath>
#include "figure.h"
#include <QGraphicsEllipseItem>

#define CIRCLETYPE 4

class Circle : public Figure
{
public:
    Circle(const QPoint& startPos, QWidget* parent);
    void draw() const override;
    void updateShapeParametrs(const QPoint& point) override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    QPoint center() const override;
    QPoint position() override;
    bool isIntersectSelection(const QRect& rect) const override;
    int getType() const override;
    void serialize(QDataStream& out) const override;
    void deserialize(QDataStream& in) override;


private:
    QPoint startPos;
    int radius = 0;
};

#endif // CIRCLE_H