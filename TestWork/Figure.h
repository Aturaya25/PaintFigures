#ifndef FIGURE_H
#define FIGURE_H

#include <QPainter>
#include <QMouseEvent>
#include <QPointF>
#include <QWidget>
#include <vector>
#include <tuple>
#include <memory>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Figure : public QWidget
{
public:
    Figure() {};
    Figure(QPoint point, QWidget* parent = nullptr);;
    virtual ~Figure() {};
    virtual void draw() const = 0;
    virtual void updateParametrs(int count, ...);
    virtual bool contains(const QPoint& point) const = 0;
    virtual void updatePosition(const QPoint& position) = 0;
    double calculateAngle(const QPoint& start, const QPoint& end) const;
    virtual QPoint position() = 0;
    virtual QPoint center() const = 0;
    virtual bool isIntersectSelection(const QRect& rect) const = 0;
    virtual void updateShapeParametrs(const QPoint& point) = 0;
    virtual int getType() const = 0;
    virtual void serialize(QDataStream& out) const = 0;
    virtual void deserialize(QDataStream& in) = 0;
    void setSelected(bool isChecked);
    void setColor(QColor _color);
    QColor color = Qt::gray;
    bool isSelected();
    QPoint delta{ 0,0 };
    QPoint mainPoint{ 0,0 };
    double _angle = 0;
    QPoint _delta;
    std::unique_ptr<QPainter> getPainter() const;
    QColor selectedColor = Qt::gray;

private:
    bool _isSelected = false;

};

#endif // FIGURE_H
