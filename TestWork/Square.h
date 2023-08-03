#ifndef SQUARE_H
#define SQUARE_H
#include "figure.h"
#include <QMainWindow>
#include <cmath>

class Square : public Figure
{
public:
    Square(const QPoint& center);
    void draw(QPainter& painter) const override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    QPoint position() override;
    void updateParametrs(int count, ...) override;
    double calculateAngle(const QPoint& start, const QPoint& end) const override;
    void rotate(double angle) override;
    ~Square();

private:
    QRect calculateSquareRect() const;
    QPoint center; // Центр квадрата
    qreal sideLength = 0; // Длина стороны квадрата
    QRect _squareRect;
};

#endif // SQUARE_H

