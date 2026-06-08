#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <vector>
#include "cellbutton.h"
#include "cell.h"

class GameController;

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    GameController* controller;
    QLabel* timerLabel;
    QLabel* flagsLabel;
    QGridLayout* gameGrid;
    std::vector<std::vector<CellButton*>> buttons;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

    void setController(GameController* ctrl);
    void initGrid(int rows, int cols);
    void updateDisplay(const std::vector<CellInfo>& revealedCells);
    void updateLabels(int time, int flags);
};

#endif