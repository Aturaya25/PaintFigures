#ifndef FIGURE_H
#define FIGURE_H

#include <QPainter>
#include <QMouseEvent>
#include <QPointF>
#include <QWidget>
#include <vector>
#include <tuple>
#include <memory>

class Figure : public QWidget
{
public:
    Figure() {};
    virtual ~Figure() {};
    virtual void draw(QPainter& painter) const = 0;
    virtual void updateParametrs(int count, ...) = 0;
    virtual bool contains(const QPoint& point) const = 0;
};

#endif // FIGURE_H
