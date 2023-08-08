#include "TestWork.h"
#include <QMouseEvent> 
#include <qtoolbutton.h>

TestWork::TestWork(QWidget* parent)
    : QMainWindow(parent)
{
    ui = new Ui::TestWorkClass;
    ui->setupUi(this);
    setMinimumSize(800, 600);
    QToolBar* toolbar = new QToolBar(this);
    addToolBar(toolbar);

    QMenu* fileMenu = new QMenu("File", this);

    QAction* openAction = fileMenu->addAction("Open");
    QAction* saveAction = fileMenu->addAction("Save");
    QAction* exitAction = fileMenu->addAction("Exit");

    QToolButton* menuButton = new QToolButton(this);
    menuButton->setText("Menu");
    menuButton->setMenu(fileMenu);
    menuButton->setPopupMode(QToolButton::InstantPopup);

    toolbar->addWidget(menuButton);

    connect(saveAction, &QAction::triggered, this, &TestWork::save);
    connect(openAction, &QAction::triggered, this, &TestWork::openFile);
    connect(exitAction, &QAction::triggered, this, &TestWork::close);

    modifyAction->setIcon(QIcon(":/TestWork/plus.png"));
    modifyAction->setCheckable(true);
    connect(modifyAction, &QAction::triggered, this, &TestWork::modifyEnabled);
    toolbar->addAction(modifyAction);

    squareAction->setIcon(QIcon(":/TestWork/square.png"));
    squareAction->setCheckable(true);
    connect(squareAction, &QAction::triggered, this, &TestWork::squareEnabled);
    toolbar->addAction(squareAction);

    rectangleAction->setIcon(QIcon(":/TestWork/rectangle.png"));
    connect(rectangleAction, &QAction::triggered, this, &TestWork::rectangleEnabled);
    rectangleAction->setCheckable(true);
    toolbar->addAction(rectangleAction);

    triangleAction->setIcon(QIcon(":/TestWork/triangle.png"));
    connect(triangleAction, &QAction::triggered, this, &TestWork::triangleEnabled);
    triangleAction->setCheckable(true);
    toolbar->addAction(triangleAction);

    dotAction->setIcon(QIcon(":/TestWork/dot.png"));
    connect(dotAction, &QAction::triggered, this, &TestWork::circleEnabled);
    dotAction->setCheckable(true);
    toolbar->addAction(dotAction);

    polygonAction->setIcon(QIcon(":/TestWork/polygon.png"));
    connect(polygonAction, &QAction::triggered, this, &TestWork::polygonEnabled);
    polygonAction->setCheckable(true);
    toolbar->addAction(polygonAction);

    toolbar->addAction(colorAction);
    connect(colorAction, &QAction::triggered, this, &TestWork::setFigureColor);

    toolbar->setMinimumHeight(30);
    toolbar->setContextMenuPolicy(Qt::NoContextMenu);
    toolbar->setMovable(false);
    ui->centralWidget->setContextMenuPolicy(Qt::NoContextMenu);
    ctrlPressed = false;

    animation.setDuration(50000);
    animation.setStartValue(0);
    animation.setEndValue(36000);
    connect(&animation, &QVariantAnimation::valueChanged, this, &TestWork::rotate360);

    modifyEnabled(true);

}

void TestWork::rotate360(QVariant value) {
    for (auto shape : selectedShapes) {
        shape->updateParametrs(1, value.toReal());
        update();
    }
}

void TestWork::modifyEnabled(bool checked)
{
    Q_UNUSED(checked)
        currentMode = Selection;
    uncheckedAllActions();
    modifyAction->setChecked(true);
}

void TestWork::squareEnabled(bool checked)
{
    Q_UNUSED(checked)
        this->currentMode = SquareCreation;
    uncheckedAllActions();
    squareAction->setChecked(true);
    this->setMouseTracking(false);
    currentShape = nullptr;
}

void TestWork::rectangleEnabled(bool checked)
{
    Q_UNUSED(checked)
        this->currentMode = RectangleCreation;
    uncheckedAllActions();
    rectangleAction->setChecked(true);
    this->setMouseTracking(false);
    currentShape = nullptr;
}

void TestWork::triangleEnabled(bool checked)
{
    Q_UNUSED(checked)
        currentMode = TriangleCreation;
    uncheckedAllActions();
    triangleAction->setChecked(true);
    this->setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    currentShape = nullptr;
}

void TestWork::circleEnabled(bool checked)
{
    Q_UNUSED(checked)
        currentMode = CircleCreation;
    uncheckedAllActions();
    dotAction->setChecked(true);
    this->setMouseTracking(false);
    currentShape = nullptr;
}

void TestWork::polygonEnabled(bool checked)
{
    Q_UNUSED(checked)
        currentMode = PolygonCreation;
    uncheckedAllActions();
    polygonAction->setChecked(true);
    this->setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    currentShape = nullptr;
}

void TestWork::setFigureColor(bool checked)
{
    Q_UNUSED(checked)
        QColor chosenColor = QColorDialog::getColor(Qt::white, this, "Выберите цвет");
    if (chosenColor.isValid()) {
        for (std::shared_ptr<Figure> shape : selectedShapes) {
            shape->setColor(chosenColor);
        }
    }
}

void TestWork::save(bool checked)
{
    Q_UNUSED(checked)
        QString filePath = QFileDialog::getSaveFileName(nullptr, "Сохранить файл", QString(), "QData files (*.qdata)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);
            for (const std::shared_ptr<Figure>& shape : shapes) {
                out << shape->getType();
                shape->serialize(out);
            }
            file.close();
        }
    }
}

void TestWork::openFile(bool checked)
{
    Q_UNUSED(checked)
        QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", QString(), "QData files (*.qdata)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            while (!in.atEnd()) {
                Mode mode;
                int intValue;
                in >> intValue;
                mode = static_cast<Mode>(intValue);
                std::shared_ptr<Figure> _shape;
                initShape(mode, _shape);
                if (_shape != nullptr) {
                    _shape->deserialize(in);
                    _shape->setSelected(false);
                    shapes.push_back(_shape);
                }
            }
            update();
            file.close();
        }
    }
}

TestWork::~TestWork()
{
    delete ui;
}


void TestWork::mousePressEvent(QMouseEvent* event)
{
    switch (event->button()) {
    case Qt::LeftButton:
    {
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
            if (!selectedShapes.empty()) {
                selected_any = false;
            }
            else {
                selected_any = true;
                selection_rect_.setTopLeft(event->pos());
                selection_rect_.setBottomRight(event->pos());
                for (auto shape : selectedShapes) {
                    shape->setSelected(false);
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

        if (currentMode == PolygonCreation) {
            if (currentShape != nullptr) {
                Polygon* _polygon = dynamic_cast<Polygon*>(currentShape.get());
                _polygon->addPoint(startPressPos);
            }
            else {
                currentShape = std::make_shared<Polygon>(startPressPos, this);
                shapes.push_back(currentShape);
            }
            update();
        }
        break;
    }
    case Qt::RightButton:
    {
        rotatedShapes.clear();
        if (!selectedShapes.empty()) {
            for (auto shape : selectedShapes) {
                rotatedShapes.push_back(shape);
            }
        }
        break;
    }
    case Qt::MiddleButton:
    {
        std::list<std::shared_ptr<Figure>> copiedShapes;
        for (auto shape : selectedShapes) {
            Mode mode = static_cast<Mode>(shape->getType());
            std::shared_ptr<Figure> _shape;
            initShape(mode, _shape);
            QByteArray byteArray;
            QDataStream out(&byteArray, QIODevice::WriteOnly);
            shape->serialize(out);

            QDataStream in(&byteArray, QIODevice::ReadOnly);
            _shape->deserialize(in);
            _shape->delta = shape->delta;
            copiedShapes.push_back(_shape);
            shapes.push_back(_shape);
        }
        clearSelectedShapes();
        for (auto shape : copiedShapes) {
            shape->setSelected(true);
            selectedShapes.push_back(shape);
        }
        update();
        break;
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
            if (selected_any)
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
        if (event->buttons() & Qt::MiddleButton) {
            if (!selectedShapes.empty()) {
                for (auto shape : selectedShapes) {
                    shape->updatePosition(event->pos());
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
                    shape->setSelected(true);
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
    if (event->key() == Qt::Key_R) {
        if (ctrlPressed)
            animation.stop();
        else
            animation.start();
    }
    if (event->key() == Qt::Key_Enter) {
        if (currentMode == PolygonCreation && currentShape != nullptr) {
            Polygon* _polygon = dynamic_cast<Polygon*>(currentShape.get());
            _polygon->setPolygonInitEnd(true);
            currentShape = nullptr;
            update();
        }
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
                if (shape->isSelected()) {
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

void TestWork::initShape(const TestWork::Mode mode, std::shared_ptr<Figure>& _shape)
{
    switch (mode) {
    case SquareCreation: {
        _shape = std::make_shared<Square>(QPoint{ 0, 0 }, this);
        break;
    }
    case RectangleCreation: {
        _shape = std::make_shared<Reactangle>(QPoint{ 0, 0 }, this);
        break;
    }
    case TriangleCreation: {
        _shape = std::make_shared<Triangle>(QPoint{ 0, 0 }, this);
        break;
    }
    case CircleCreation: {
        _shape = std::make_shared<Circle>(QPoint{ 0, 0 }, this);
        break;
    }
    case PolygonCreation: {
        _shape = std::make_shared<Polygon>(QPoint{ 0, 0 }, this);
        break;
    }
    default:
        break;
    }
}

void TestWork::uncheckedAllActions()
{
    for (auto action : actions) {
        action->setChecked(false);
    }
}