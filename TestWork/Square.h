#ifndef SQUARE_H
#define SQUARE_H
#include "figure.h"
#include <QMainWindow>

class Square : public Figure
{
public:
    Square(const QPointF& center, qreal sideLength);
    void draw(QPainter& painter) const override;
    bool contains(const QPoint& point) const override;
    void updateParametrs(int count, ...) override;
    ~Square();

private:
    QRectF calculateSquareRect() const;
    QPointF center; // Центр квадрата
    qreal sideLength; // Длина стороны квадрата
    QRectF _squareRect;
};

#endif // SQUARE_H

