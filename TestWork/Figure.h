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
    virtual void updatePosition(const QPoint& position) = 0;
    virtual double calculateAngle(const QPoint& start, const QPoint& end) const = 0;
    virtual void rotate(double angle) = 0;
    virtual QPoint position() = 0;
    void setSelected(bool isChecked);
    QColor color = Qt::gray;
    bool _isSelected = false;
    QPoint delta{ 0,0 };
};

#endif // FIGURE_H
