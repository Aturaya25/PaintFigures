#ifndef SQUARE_H
#define SQUARE_H
#include "figure.h"
#include <QMainWindow>

class Square : public Figure
{
public:
    Square(const QPointF& center, qreal sideLength);
    void draw(QPainter& painter) const override;
    void updateParametrs(int count, ...) override;
    ~Square();

private:
    QPointF center; // Центр квадрата
    qreal sideLength; // Длина стороны квадрата
};

#endif // SQUARE_H

