#ifndef REACTANGLE_H
#define REACTANGLE_H
#include "figure.h"

#define REACTANGLETYPE 2

class Reactangle : public Figure
{
public:
    Reactangle(const QPoint& startPos, QWidget* parent);
    void draw() const override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    QPoint center() const override;
    QPoint position() override;
    void updateShapeParametrs(const QPoint& point) override;
    bool isIntersectSelection(const QRect& rect) const override;
    int getType() const override;
    void serialize(QDataStream& out) const override;
    void deserialize(QDataStream& in) override;

private:
    QPoint startPos;
    QPoint currentPos;
};

#endif // REACTANGLE_H