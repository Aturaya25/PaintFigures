#include "TestWork.h"
#include <QMouseEvent> 

TestWork::TestWork(QWidget* parent)
    : QMainWindow(parent)
{
    ui = new Ui::TestWorkClass;
    ui->setupUi(this);
    setMinimumSize(800, 600);
    QToolBar *toolbar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolbar);

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
    toolbar->setContextMenuPolicy(Qt::NoContextMenu);
    toolbar->setMovable(false);
    ui->centralWidget->setContextMenuPolicy(Qt::NoContextMenu);
    ctrlPressed = false;
}

TestWork::~TestWork()
{}


void TestWork::squareEnabled(bool checked)
{
    this->currentMode = SquareCreation;
    this->setMouseTracking(false);
    currentShape = nullptr;
}

void TestWork::rectangleEnabled(bool checked)
{
    this->currentMode = RectangleCreation;
    this->setMouseTracking(false);
    currentShape = nullptr;
}

void TestWork::triangleEnabled(bool checked)
{
    currentMode = TriangleCreation;
    this->setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    currentShape = nullptr;
}

void TestWork::circleEnabled(bool checked)
{
    currentMode = CircleCreation;
    this->setMouseTracking(false);
    currentShape = nullptr;
}

void TestWork::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        startPressPos = event->pos();
        if (currentMode == Selection) {
            bool isEmptyPoint = true;
            for (auto it = shapes.rbegin(); it != shapes.rend(); it++) {
                auto shape = *it;
                if (shape->contains(startPressPos)) {
                    currentShape = shape;
                    if (!shape->isSelected()) {
                        if (!ctrlPressed) {
                            clearSelectedShapes();
                        }
                    }
                    selectedShapes.push_back(shape);
                    isEmptyPoint = false;
                    break;
                }
            }
            if (!ctrlPressed && isEmptyPoint) {
                clearSelectedShapes();
            }
            for (auto shape : selectedShapes) {
                shape->setSelected(true);
                shape->delta = shape->position() - startPressPos;
            }
            if (!selectedShapes.empty() && !ctrlPressed) {
                selected_any = false;
            }
            else {
                selected_any = true;
                selection_rect_.setTopLeft(event->pos());
                selection_rect_.setBottomRight(event->pos());
                if (!ctrlPressed){
                    for (auto shape : selectedShapes) {
                        shape->setSelected(false);
                    }
                }
            }
            update();
        }
        else {
            this->clearSelectedShapes();
        }
        if (currentMode == SquareCreation) {
            currentPos = startPressPos;
            QPoint center = (currentPos + startPressPos) / 2.0;
            currentShape = std::make_shared<Square>(center, this);
            shapes.push_back(currentShape);
            update();
        }
        if (currentMode == RectangleCreation) {
            currentShape = std::make_shared<Reactangle>(startPressPos, this);
            shapes.push_back(currentShape);
            update();
        }
        if (currentMode == TriangleCreation) {
            if (triangePointCount == 0) {
                currentShape = std::make_shared<Triangle>(startPressPos, this);
                shapes.push_back(currentShape);
                triangePointCount++;
            }
            else {
                currentShape->updateParametrs(2, startPressPos.x(), startPressPos.y());
                Triangle* triangle = dynamic_cast<Triangle*>(currentShape.get());
                triangePointCount++;
                triangle->updatePointCount();
                if (triangePointCount == 3) {
                    update();
                    triangePointCount = 0;
                }
            }
        }
        if (currentMode == CircleCreation) {
            currentShape = std::make_shared<Circle>(startPressPos, this);
            shapes.push_back(currentShape);
            update();
        }
    }
    if (event->button() == Qt::RightButton) {
        rotatedShapes.clear();
        if (!selectedShapes.empty()) {
            for (auto shape : selectedShapes) {
                rotatedShapes.push_back(shape);
            }
        }
    }
}

void TestWork::mouseMoveEvent(QMouseEvent* event)
{
    if (currentShape != nullptr) {
        currentPos = event->pos();
        if (currentMode != Selection) {
            currentShape->updateParametrs(2, currentPos.x(), currentPos.y());
        }
    }
    if (currentMode == Selection) {
        if (event->buttons() & Qt::LeftButton) {
            if (selected_any )
            {
                selection_rect_.setBottomRight(event->pos());
            }
            else {

                for (auto shape : selectedShapes) {
                    shape->updatePosition(event->pos());
                }
            }
            update();
        }
        if (event->buttons() & Qt::RightButton) {
            if (!rotatedShapes.empty()) {
                for (auto shape : rotatedShapes) {
                    double angle = shape->calculateAngle(startPressPos, currentPos);
                    shape->updateParametrs(1, angle);
                }
                update();
            }
        }
    }
    update();
}

void TestWork::mouseReleaseEvent(QMouseEvent* event)
{

    if (currentMode != Selection && event->button() == Qt::LeftButton) {
        startPressPos = QPoint();
        update();
    }
    else if (event->button() == Qt::RightButton) {
        isRotationShapes = false;
        rotatedShapes.clear();
        startPressPos = QPoint();
        update();
    }
    else {
        if (selected_any) {
            for (auto shape : shapes)
            {
                if (shape->isSelected() || shape->contains(selection_rect_.topLeft()) || shape->contains(selection_rect_.bottomRight()))
                {
                    shape->setSelected(true);
                }
            }
            update();
            selected_any = false;
        }
    }
}

void TestWork::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control)
    {
        ctrlPressed = true;
    }
    if (event->key() == Qt::Key_D) {
        for (auto it = shapes.begin(); it != shapes.end(); ) {
            if ((*it)->isSelected()) {
                it = shapes.erase(it);
            }
            else {
                ++it;
            }
        }
        update();
    }
}

void TestWork::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control)
    {
        ctrlPressed = false;
    }
}

void TestWork::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    for (const auto& shape : shapes) {
        if (shape != nullptr)
            shape->draw();
    }
    if (selected_any)
    {
        QPainter painter2(this);
        painter2.setRenderHint(QPainter::Antialiasing, true);
        painter2.setPen(Qt::DashLine);
        QColor selectionColor(Qt::blue);
        selectionColor.setAlpha(100);
        painter2.setBrush(selectionColor);
        painter2.drawRect(selection_rect_);
        painter2.end();
        for (auto shape : shapes) {
            if (shape->isIntersectSelection(selection_rect_)) {
                shape->setSelected(true);
                selectedShapes.push_back(shape);
            }
            else {
                if (shape->isSelected() && !ctrlPressed) {
                    selectedShapes.remove(shape);
                    shape->setSelected(false);
                }
            }
        }
    }
}

void TestWork::clearSelectedShapes()
{
    for (auto shape : selectedShapes) {
        shape->setSelected(false);
        shape->delta = { 0, 0 };
    }
    selectedShapes.clear();
}

void TestWork::modifyEnabled(bool checked)
{
    currentMode = Selection;
}
