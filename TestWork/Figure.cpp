#include "figure.h"
#include <cstdarg>

Figure::Figure(QPoint point, QWidget* parent) :QWidget(parent), mainPoint(point)
{

}

void Figure::updateParametrs(int count, ...)
{
    va_list args;
    va_start(args, count);
    if (count == 1) {
        double angle = va_arg(args, double);
        if (angle != 0) {
            _angle = angle;
        }
    }
    else {
        int x = va_arg(args, int);
        int y = va_arg(args, int);
        QPoint currentPos = QPoint(x, y);
        updateShapeParametrs(currentPos);
    }
    va_end(args);
}

double Figure::calculateAngle(const QPoint& start, const QPoint& end) const
{
    QPointF _center = center();
    double startX = start.x() - _center.x();
    double startY = start.y() - _center.y();
    double endX = end.x() - _center.x();
    double endY = end.y() - _center.y();
    double startAngle = std::atan2(startY, startX);
    double endAngle = std::atan2(endY, endX);
    double angle = endAngle - startAngle;
    double angleInDegrees = angle * (180.0 / M_PI);
    return angleInDegrees;
}

void Figure::setSelected(bool isChecked)
{
    if (isChecked) {
        color = QColor("#bdfffb");
        _isSelected = true;
    }
    else {
        color = selectedColor;
        _isSelected = false;
    }
}

void Figure::setColor(QColor _color)
{
    selectedColor = _color;
}

bool Figure::isSelected()
{
    return _isSelected;
}

std::unique_ptr<QPainter> Figure::getPainter() const {
    std::unique_ptr<QPainter> p = std::make_unique<QPainter>(dynamic_cast<QWidget*>(this->parent()));
    p->setRenderHint(QPainter::Antialiasing, true);
    p->setPen(Qt::black);
    return p;
}