#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <iostream>
#include <QPoint>
#include <QAction>
#include <QFileDialog>
#include <QColorDialog>
#include <qdatastream.h>
#include <qtoolbar.h>
#include "ui_TestWork.h"
#include <QVariantAnimation>
#include "figure.h"
#include "square.h"
#include "reactangle.h"
#include "triangle.h"
#include "circle.h"
#include "polygon.h"

class TestWork : public QMainWindow
{
    Q_OBJECT

public:
    TestWork(QWidget* parent = nullptr);
    ~TestWork();

    enum Mode {
        Selection,
        SquareCreation,
        RectangleCreation,
        TriangleCreation,
        CircleCreation,
        PolygonCreation
    };

public slots:
    void rotate360(QVariant value);
private slots:
    void modifyEnabled(bool checked);
    void squareEnabled(bool checked);
    void rectangleEnabled(bool checked);
    void triangleEnabled(bool checked);
    void circleEnabled(bool checked);
    void polygonEnabled(bool checked);
    void setFigureColor(bool checked);
    void save(bool checked);
    void openFile(bool checked);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::TestWorkClass* ui;
    QAction* modifyAction = new QAction(this);
    QAction* squareAction = new QAction(this);
    QAction* rectangleAction = new QAction(this);
    QAction* triangleAction = new QAction(this);
    QAction* dotAction = new QAction(this);
    QAction* polygonAction = new QAction(this);
    QAction* colorAction = new QAction("Color", this);

    bool ctrlPressed;
    QPoint rectStartPos;
    QPoint centerPoint;
    QRect selectionRect;

    std::vector<QAction*> actions{ modifyAction, squareAction, rectangleAction, triangleAction, dotAction, polygonAction, colorAction };

    void clearSelectedShapes();
    void initShape(const Mode mode, std::shared_ptr<Figure>& _shape);
    void uncheckedAllActions();

    std::list<std::shared_ptr<Figure>> shapes;
    std::list<std::shared_ptr<Figure>> selectedShapes;
    std::list<std::shared_ptr<Figure>> rotatedShapes;
    Mode currentMode = Selection;
    QPoint startPressPos;
    QPoint currentPos;
    std::shared_ptr<Figure> currentShape;
    int triangePointCount = 0;
    bool selected_any = false;
    bool isRotationShapes = false;
    QRect selection_rect_;
    QVariantAnimation animation;
};
