#ifndef REACTANGLE_H
#define REACTANGLE_H
#include "figure.h"

class Reactangle : public Figure
{
public:
    Reactangle(const QPoint& startPos);
    void draw(QPainter& painter) const override;
    void updateParametrs(int count, ...) override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    double calculateAngle(const QPoint& start, const QPoint& end) const override;
    QPoint position() override;
    void rotate(double angle) override;

private:
    QPoint startPos;
    QPoint currentPos;
};

#endif // REACTANGLE_H