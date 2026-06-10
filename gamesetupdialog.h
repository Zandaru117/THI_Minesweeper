#ifndef GAMESETUPDIALOG_H
#define GAMESETUPDIALOG_H

#include <QDialog>

namespace Ui {
class GameSetupDialog;
}

class GameSetupDialog : public QDialog {
    Q_OBJECT

public:
    explicit GameSetupDialog(QWidget* parent = nullptr);
    ~GameSetupDialog();

    int getRows() const;
    int getCols() const;
    int getMines() const;

private slots:
    void on_startButton_clicked();
    void on_cancelButton_clicked();
    void updateMaxMines();
    void updateSpinBoxes(int rows, int cols, int mines, bool enableCustom);

private:
    Ui::GameSetupDialog* ui;
};

#endif