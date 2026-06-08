#ifndef ENDGAMEDIALOG_H
#define ENDGAMEDIALOG_H

#include <QDialog>

namespace Ui {
class EndGameDialog;
}

class EndGameDialog : public QDialog {
    Q_OBJECT

public:
    explicit EndGameDialog(bool isWin, int elapsedTime, QWidget* parent = nullptr);
    ~EndGameDialog();

private slots:
    void on_restartButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::EndGameDialog* ui;
};

#endif