#include "mainwindow.h"
#include "gamecontroller.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    controller(nullptr),
    timerLabel(nullptr),
    flagsLabel(nullptr),
    gameGrid(nullptr)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // ВЕРХНЕЕ МЕНЮ
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* gameMenu = menuBar->addMenu("Игра");

    QAction* newGameAction = gameMenu->addAction("Новая игра / Сложность");
    QAction* exitAction = gameMenu->addAction("Выход");

    setMenuBar(menuBar);

    connect(newGameAction, &QAction::triggered, this, [this]() {
        if (controller) controller->startNewGame(0, 0, 0);
    });
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    // ПАНЕЛЬ ИНФОРМАЦИИ
    QHBoxLayout* topLayout = new QHBoxLayout();
    timerLabel = new QLabel("Время: 0", this);
    flagsLabel = new QLabel("Мины: 0", this);
    topLayout->addWidget(timerLabel, 0, Qt::AlignCenter);
    topLayout->addWidget(flagsLabel, 0, Qt::AlignCenter);

    gameGrid = new QGridLayout();
    gameGrid->setSpacing(1);
    gameGrid->setSizeConstraint(QLayout::SetFixedSize); // Запрещаем сетке растягиваться

    mainLayout->addLayout(topLayout);

    QHBoxLayout* gridContainerLayout = new QHBoxLayout();
    gridContainerLayout->addStretch(1);
    gridContainerLayout->addLayout(gameGrid);
    gridContainerLayout->addStretch(1);

    mainLayout->addStretch(1);
    mainLayout->addLayout(gridContainerLayout);
    mainLayout->addStretch(1);

    setCentralWidget(centralWidget);

    resize(400, 300);
}

void MainWindow::setController(GameController* ctrl) {
    this->controller = ctrl;
}

void MainWindow::initGrid(int rows, int cols) {
    if (!gameGrid) return;

    //Безопасная очистка старых элементов
    QLayoutItem* item;
    while ((item = gameGrid->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->hide();
            delete item->widget();
        }
        delete item;
    }

    buttons.clear();
    buttons.resize(rows, std::vector<CellButton*>(cols, nullptr));

    gameGrid->setSizeConstraint(QLayout::SetFixedSize);
    gameGrid->setSpacing(1); // Минимальный отступ между кнопками

    QWidget* container = centralWidget();
    if (!container) container = this;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            CellButton* button = new CellButton(r, c, container);

            button->setFixedSize(30, 30);

            gameGrid->addWidget(button, r, c);
            buttons[r][c] = button;

            connect(button, &CellButton::leftClicked, this, [this, r, c]() {
                if (controller) controller->handleCellClick(r, c);
            });
            connect(button, &CellButton::rightClicked, this, [this, r, c]() {
                if (controller) controller->handleCellRightClick(r, c);
            });
        }
    }

    if (centralWidget() && centralWidget()->layout()) {
        centralWidget()->layout()->invalidate();
        centralWidget()->layout()->activate();
    }
}

void MainWindow::updateDisplay(const std::vector<CellInfo>& revealedCells) {
    for (const auto& info : revealedCells) {
        if (info.row < 0 || info.row >= static_cast<int>(buttons.size()) ||
            info.col < 0 || info.col >= static_cast<int>(buttons[info.row].size())) {
            continue;
        }

        CellButton* btn = buttons[info.row][info.col];
        if (!btn) continue;

        if (info.isRevealed) {
            btn->setEnabled(false);
            if (info.isMine) {
                btn->setText("💣");
                btn->setStyleSheet("background-color: red; color: black; font-weight: bold;");
            } else {
                if (info.neighborMinesCount > 0) {
                    btn->setText(QString::number(info.neighborMinesCount));
                } else {
                    btn->setText("");
                }
                btn->setStyleSheet("background-color: #E0E0E0; border: 1px solid #B0B0B0;");
            }
        } else if (info.isFlagged) {
            btn->setText("🚩");
            btn->setStyleSheet("color: red; font-weight: bold;");
        } else {
            btn->setText("");
            btn->setStyleSheet("");
        }
    }
}

void MainWindow::updateLabels(int time, int flags) {
    if (timerLabel) timerLabel->setText(QString("Время: %1").arg(time));
    if (flagsLabel) flagsLabel->setText(QString("Осталось мин: %1").arg(flags));
}