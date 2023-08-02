#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <iostream>
#include <qtoolbar.h>
#include <qdebug.h>
#include <qt>
#include "ui_TestWork.h"
#include "Figure.h"
#include "Square.h"
#include "Reactangle.h"
#include "Triangle.h"
#include "Circle.h"

class TestWork : public QMainWindow
{
    Q_OBJECT

public:
    TestWork(QWidget *parent = nullptr);
    ~TestWork();

    enum Mode {
        Selection,
        SquareCreation,
        RectangleCreation,
        TriangleCreation,
        CircleCreation
    };

    void setMode(Mode mode);
    void clearAllShapes();

private slots:
    void modifyEnabled(bool checked);
    void squareEnabled(bool checked);
    void rectangleEnabled(bool checked);
    void triangleEnabled(bool checked);
    void circleEnabled(bool checked);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;


private:
    Ui::TestWorkClass ui;
    QAction *modifyAction = new QAction(this);
    QAction *squareAction = new QAction(this);
    QAction *rectangleAction = new QAction(this);
    QAction* triangleAction = new QAction(this);
    QAction* dotAction = new QAction(this);

    bool ctrlPressed;
    bool drawingRect;
    QPoint rectStartPos;
    QPoint centerPoint;
    bool drawingSquare;
    QRect selectionRect;

    std::vector<std::shared_ptr<Figure>> shapes;
    Mode currentMode = Selection;
    QPointF startPressPos;
    QPointF currentPos;
    std::shared_ptr<Figure> currentShape;
    Figure* stupidPointer;
    bool drawingRectangle = false;
    int triangePointCount = 0;
};
