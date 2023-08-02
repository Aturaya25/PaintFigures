#include "TestWork.h"
#include <QMouseEvent> 

TestWork::TestWork(QWidget* parent)
    : QMainWindow(parent)
{
    setMinimumSize(800, 600);
    QToolBar *toolbar = new QToolBar(this);
    addToolBar(toolbar);

    modifyAction->setIcon(QIcon::fromTheme(":/TestWork/plus.png"));
    connect(modifyAction, &QAction::triggered, this, &TestWork::modifyEnabled);
    toolbar->addAction(modifyAction);

    squareAction->setIcon(QIcon::fromTheme(":/TestWork/square.png"));
    connect(squareAction, &QAction::triggered, this, &TestWork::squareEnabled);
    toolbar->addAction(squareAction);

    rectangleAction->setIcon(QIcon::fromTheme(":/TestWork/rectangle.png"));
    connect(rectangleAction, &QAction::triggered, this, &TestWork::rectangleEnabled);
    toolbar->addAction(rectangleAction);

    triangleAction->setIcon(QIcon::fromTheme(":/TestWork/triangle.png"));
    connect(triangleAction, &QAction::triggered, this, &TestWork::triangleEnabled);
    toolbar->addAction(triangleAction);

    dotAction->setIcon(QIcon::fromTheme(":/TestWork/dot.png"));
    connect(dotAction, &QAction::triggered, this, &TestWork::circleEnabled);
    toolbar->addAction(dotAction);

    toolbar->setMinimumHeight(30);
    ctrlPressed = false;
    drawingRect = false;

    drawingSquare = false;
}

TestWork::~TestWork()
{}

void TestWork::setMode(Mode mode)
{
    this->currentMode = mode;
}

void TestWork::clearAllShapes()
{
    this->shapes.clear();
}

void TestWork::squareEnabled(bool checked)
{
    this->currentMode = SquareCreation;
    setMouseTracking(false);
}

void TestWork::rectangleEnabled(bool checked)
{
    this->currentMode = RectangleCreation;
    setMouseTracking(false);
}

void TestWork::triangleEnabled(bool checked)
{
    currentMode = TriangleCreation;
    setMouseTracking(true);
}

void TestWork::circleEnabled(bool checked)
{
    currentMode = CircleCreation;
    setMouseTracking(false);
}

void TestWork::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {

        if (currentMode == Selection) {

        }
        if (currentMode == SquareCreation) {
            startPressPos = event->pos();
            currentPos = startPressPos;
            QPointF center = (currentPos + startPressPos) / 2.0;
            currentShape = std::make_shared<Square>(center, 0);
            shapes.push_back(currentShape);
            update();
        }
        if (currentMode == RectangleCreation) {
            startPressPos = event->pos();
            currentShape = std::make_shared<Reactangle>(startPressPos);
            shapes.push_back(currentShape);
            update();
        }
        if (currentMode == TriangleCreation) {
            if (triangePointCount == 0) {
                startPressPos = event->pos();
                currentShape = std::make_shared<Triangle>(startPressPos);
                shapes.push_back(currentShape);
                triangePointCount++;
            }
            else {
                currentPos = event->pos();
                Triangle* triangle = dynamic_cast<Triangle*>(currentShape.get());
                triangle->updateParametrs(2, currentPos.x(), currentPos.y());
                triangePointCount++;
                triangle->updatePointCount();
                if (triangePointCount == 3) {
                    update();
                    triangePointCount = 0;
                }
            }
        }
        if (currentMode == CircleCreation) {
            startPressPos = event->pos();
            currentShape = std::make_shared<Circle>(startPressPos);
            shapes.push_back(currentShape);
            update();
        }
    }
}

void TestWork::mouseReleaseEvent(QMouseEvent* event)
{
    if (currentMode == SquareCreation && event->button() == Qt::LeftButton) {
        startPressPos = QPointF();
        update();
    }
    if (currentMode == RectangleCreation && event->button() == Qt::LeftButton) {
        startPressPos = QPointF();
        update();
    }
    if (currentMode == TriangleCreation && event->button() == Qt::LeftButton) {
        startPressPos = QPointF();
    }
    if (currentMode == CircleCreation && event->button() == Qt::LeftButton) {
        startPressPos = QPointF();
        update();
    }
}

void TestWork::mouseMoveEvent(QMouseEvent* event)
{
    if (currentShape != nullptr) {
        currentPos = event->pos();
        if (currentMode == SquareCreation) {
            Square* s = dynamic_cast<Square*>(currentShape.get());
            qreal sideLength = qMax(qAbs(currentPos.x() - startPressPos.x()), qAbs(currentPos.y() - startPressPos.y())) * 2;
            s->updateParametrs(1, sideLength);
            update();
        }
        else if (currentMode == RectangleCreation) {
            // Создание нового прямоугольника и добавление его в список shapes
            Reactangle* r = dynamic_cast<Reactangle*>(currentShape.get());
            r->updateParametrs(2, currentPos.x(), currentPos.y());
            update();
        } else if (currentMode == TriangleCreation && triangePointCount != 0) {
            // Создание нового треугольника и добавление его в список shapes
            Triangle* triangle = dynamic_cast<Triangle*>(currentShape.get());
            triangle->updateParametrs(2, currentPos.x(), currentPos.y());
            update();

        } else if (currentMode == CircleCreation) {
            // Создание новой окружности и добавление ее в список shapes
            Circle* circle = dynamic_cast<Circle*>(currentShape.get());
            circle->updateParametrs(2, currentPos.x(), currentPos.y());
            update();
        }
    }
}

void TestWork::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control)
    {
        ctrlPressed = true;
    }

    QMainWindow::keyPressEvent(event);
}

void TestWork::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control)
    {
        ctrlPressed = false;
    }

    QMainWindow::keyReleaseEvent(event);
}

void TestWork::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);

    for (const auto& shape : shapes) {
        if (shape != nullptr)
            shape->draw(painter);
    }
    painter.end();
}

void TestWork::modifyEnabled(bool checked)
{
    currentMode = Selection;
}
