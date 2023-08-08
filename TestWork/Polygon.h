#pragma once
#include "figure.h"

#define POLYGONTYPE 5


class Polygon : public Figure
{
public:
    Polygon(const QPoint& startPos, QWidget* parent);

public:
    void draw() const override;
    bool contains(const QPoint& point) const override;
    void updatePosition(const QPoint& position) override;
    QPoint position() override;
    QPoint center() const override;
    bool isIntersectSelection(const QRect& rect) const override;
    void updateShapeParametrs(const QPoint& point) override;
    bool isPolygonInitEnd() const;
    void setPolygonInitEnd(const bool isEnd);
    void addPoint(const QPoint p);
    int getType() const override;
    void serialize(QDataStream& out) const override;
    void deserialize(QDataStream& in) override;


private:
    std::vector<QPoint> polygonPoints;
    bool endPolygonInit = false;
    QPoint startPoint;
    QPoint currentPoint;
};

