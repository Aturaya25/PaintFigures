#ifndef REACTANGLE_H
#define REACTANGLE_H
#include "figure.h"

class Reactangle : public Figure
{
public:
    Reactangle(const QPointF& startPos);
    void draw(QPainter& painter) const override;
    void updateParametrs(int count, ...) override;

private:
    QPointF startPos;
    QPointF currentPos;
};

#endif // REACTANGLE_H