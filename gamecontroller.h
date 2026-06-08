#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>

class MainWindow;
class MinesweeperEngine;

class GameController : public QObject {
    Q_OBJECT
private:
    MainWindow* view;
    MinesweeperEngine* gameEngine;
    QTimer* gameTimer;
    int elapsedTime;
    int remainingMines;
    bool isFirstMove;
    bool isGameActive;

public:
    explicit GameController(MainWindow* w, QObject* parent = nullptr);
    ~GameController();

    void startNewGame(int rows, int cols, int mines);

public slots:
    void handleCellClick(int row, int col);
    void handleCellRightClick(int row, int col);
    void onTimerTick();
};

#endif