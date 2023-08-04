#ifndef SQUARE_H
#define SQUARE_H
#include "figure.h"
#include <QMainWindow>
#include <cmath>

class Square : public Figure
{
public:
    Square(const QPoint& center);
    Square(const QPoint& center, QWidget* parent = nullptr);
    void draw() const override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    QPoint position() override;
    QPoint center() const override;
    void updateShapeParametrs(const QPoint& point) override;
    bool isIntersectSelection(const QRect& rect) const override;
    ~Square();

private:
    QRect calculateSquareRect() const;
    QPoint _center;
    qreal sideLength = 0;
};

#endif // SQUARE_H

