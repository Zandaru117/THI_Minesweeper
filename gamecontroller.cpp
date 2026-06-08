#include "gamecontroller.h"
#include "mainwindow.h"
#include "gamesetupdialog.h"
#include "endgamedialog.h"
#include "minesweeperengine.h"
#include "cell.h"

GameController::GameController(MainWindow* w, QObject* parent)
    : QObject(parent),
    view(w),
    gameEngine(nullptr),
    gameTimer(nullptr),
    elapsedTime(0),
    remainingMines(0),
    isFirstMove(true),
    isGameActive(false)
{
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameController::onTimerTick);
}

GameController::~GameController() {
    if (gameEngine) {
        gameEngine->destroy();
    }
}

void GameController::startNewGame(int rows, int cols, int mines) {
    if (rows == 0 || cols == 0) {
        GameSetupDialog setupDlg(static_cast<QWidget*>(view));
        if (setupDlg.exec() == QDialog::Accepted) {
            rows = setupDlg.getRows();
            cols = setupDlg.getCols();
            mines = setupDlg.getMines();
        } else {
            if (!gameEngine) {
                rows = 9;
                cols = 9;
                mines = 10;
            } else {
                return;
            }
        }
    }

    if (gameEngine) {
        gameEngine->destroy();
        gameEngine = nullptr;
    }

    gameEngine = new MinesweeperEngine(rows, cols, mines);
    elapsedTime = 0;
    remainingMines = mines;
    isFirstMove = true;
    isGameActive = true;

    gameTimer->stop();

    if (view) {
        view->initGrid(rows, cols);
        view->updateLabels(elapsedTime, remainingMines);
    }
}

void GameController::handleCellClick(int row, int col) {
    if (!isGameActive || !gameEngine) return;

    if (isFirstMove) {
        gameEngine->generateBoard(row, col);
        isFirstMove = false;
        gameTimer->start(1000);
    }

    std::vector<CellInfo> changes = gameEngine->revealCell(row, col);
    if (view) view->updateDisplay(changes);

    for (const auto& cell : changes) {
        if (cell.isMine && cell.isRevealed) {
            gameTimer->stop();
            isGameActive = false;

            EndGameDialog endDlg(false, elapsedTime, static_cast<QWidget*>(view));
            if (endDlg.exec() == QDialog::Accepted) {
                startNewGame(gameEngine->getRows(), gameEngine->getCols(), gameEngine->getTotalMines());
            }
            return;
        }
    }

    if (gameEngine->checkWinCondition()) {
        gameTimer->stop();
        isGameActive = false;

        EndGameDialog endDlg(true, elapsedTime, static_cast<QWidget*>(view));
        if (endDlg.exec() == QDialog::Accepted) {
            startNewGame(gameEngine->getRows(), gameEngine->getCols(), gameEngine->getTotalMines());
        }
    }
}

void GameController::handleCellRightClick(int row, int col) {
    if (!isGameActive || isFirstMove || !gameEngine) return;

    CellInfo updatedCell = gameEngine->toggleFlag(row, col);

    if (updatedCell.isFlagged) {
        remainingMines--;
    } else {
        remainingMines++;
    }

    std::vector<CellInfo> changes = { updatedCell };
    if (view) {
        view->updateDisplay(changes);
        view->updateLabels(elapsedTime, remainingMines);
    }
}

void GameController::onTimerTick() {
    elapsedTime++;
    if (view) view->updateLabels(elapsedTime, remainingMines);
}