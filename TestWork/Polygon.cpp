#include "Polygon.h"
Polygon::Polygon(const QPoint& startPos, QWidget* parent) : Figure(startPos, parent), startPoint(startPos)
{
    polygonPoints.push_back(startPoint);
}

void Polygon::draw() const
{
    auto painter = getPainter();
    if (polygonPoints.size() > 0) {
        if (!endPolygonInit) {
            for (size_t i = 1; i < polygonPoints.size(); i++) {
                painter->drawLine(polygonPoints[i - 1], polygonPoints[i]);
            }
            if (!currentPoint.isNull()) {
                painter->drawLine(polygonPoints[polygonPoints.size() - 1], currentPoint);
            }
        }
        else {
            painter->setBrush(color);
            QPolygon polygon;
            for (size_t i = 0; i < polygonPoints.size(); i++) {
                polygon << polygonPoints[i];
            }
            if (_angle != 0) {
                painter->translate(this->center());
                painter->rotate(_angle);
                painter->translate(-this->center());
            }
            painter->drawPolygon(polygon);
        }
    }
}

bool Polygon::contains(const QPoint& point) const
{
    QPolygon polygon;
    for (size_t i = 0; i < polygonPoints.size(); i++)
        polygon << polygonPoints[i];


    int numVertices = polygon.size();
    int intersectCount = 0;

    for (int i = 0; i < numVertices; ++i) {
        const QPoint& vertex1 = polygon[i];
        const QPoint& vertex2 = polygon[(i + 1) % numVertices];

        if ((vertex1.y() > point.y() && vertex2.y() <= point.y()) ||
            (vertex2.y() > point.y() && vertex1.y() <= point.y())) {
            double intersectX = vertex1.x() + (static_cast<double>(point.y() - vertex1.y()) / static_cast<double>(vertex2.y() - vertex1.y())) * (vertex2.x() - vertex1.x());

            if (intersectX > point.x()) {
                ++intersectCount;
            }
        }
    }
    return (intersectCount % 2 != 0);

}

void Polygon::updatePosition(const QPoint& position)
{
    for (QPoint& point : polygonPoints) {
        point -= startPoint - position - delta;
    }
    startPoint = position + delta;
}

QPoint Polygon::position()
{
    return startPoint;
}

QPoint Polygon::center() const
{
    if (polygonPoints.empty()) {
        return QPoint(0, 0); // ¬озвращаем нулевую точку дл€ пустого полигона
    }

    int totalX = 0;
    int totalY = 0;

    for (const QPoint& point : polygonPoints) {
        totalX += point.x();
        totalY += point.y();
    }

    int centerX = totalX / polygonPoints.size();
    int centerY = totalY / polygonPoints.size();

    return QPoint(centerX, centerY);
}

bool Polygon::isIntersectSelection(const QRect& rect) const
{
    auto c = center();
    bool angleInPolygon = contains(rect.topLeft()) || contains(rect.topRight()) || contains(rect.bottomLeft()) || contains(rect.bottomRight());
    bool circleCenterInRect = rect.contains(c);
    for (const QPoint& p : polygonPoints) {
        if (rect.contains(p)) {
            return true;
        }
    }
    return angleInPolygon || circleCenterInRect;
}

void Polygon::updateShapeParametrs(const QPoint& point)
{
    currentPoint = point;
}

bool Polygon::isPolygonInitEnd() const
{
    return endPolygonInit;
}

void Polygon::setPolygonInitEnd(const bool isEnd)
{
    endPolygonInit = isEnd;
}

void Polygon::addPoint(const QPoint p)
{
    polygonPoints.push_back(p);
    currentPoint = QPoint();
}

int Polygon::getType() const
{
    return POLYGONTYPE;
}

void Polygon::serialize(QDataStream& out) const
{
    out << startPoint << _angle << endPolygonInit << selectedColor;
    out << static_cast<qint32>(polygonPoints.size());
    for (auto p : polygonPoints)
        out << p;
}

void Polygon::deserialize(QDataStream& in)
{
    qint32 numPoints;
    polygonPoints.clear();
    in >> startPoint >> _angle >> endPolygonInit >> selectedColor >> numPoints;
    for (qint32 i = 0; i < numPoints; ++i) {
        QPoint p;
        in >> p;
        polygonPoints.push_back(p);
    }
}

