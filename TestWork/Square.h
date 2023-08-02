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
    QPointF center; // ����� ��������
    qreal sideLength; // ����� ������� ��������
};

#endif // SQUARE_H

