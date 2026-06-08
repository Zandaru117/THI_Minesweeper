#include "endgamedialog.h"
#include "ui_endgamedialog.h"

EndGameDialog::EndGameDialog(bool isWin, int elapsedTime, QWidget* parent)
    : QDialog(parent), ui(new Ui::EndGameDialog)
{
    ui->setupUi(this);

    if (isWin) {
        ui->resultLabel->setText("Поздравляем! Вы победили!");
        ui->resultLabel->setStyleSheet("color: #4CAF50; font-weight: bold; font-size: 16px;");
    } else {
        ui->resultLabel->setText("Игра окончена. Взрыв!");
        ui->resultLabel->setStyleSheet("color: #F44336; font-weight: bold; font-size: 16px;");
    }

    ui->statsLabel->setText(QString("Время прохождения: %1 сек.").arg(elapsedTime));
}

EndGameDialog::~EndGameDialog() {
    delete ui;
}

void EndGameDialog::on_restartButton_clicked() {
    accept();
}

void EndGameDialog::on_exitButton_clicked() {
    reject();
}