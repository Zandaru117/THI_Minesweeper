#include "gamesetupdialog.h"
#include "ui_gamesetupdialog.h"

GameSetupDialog::GameSetupDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::GameSetupDialog)
{
    ui->setupUi(this);

    // Привязываем логику переключения пресетов сложности
    connect(ui->radioNovice, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) updateSpinBoxes(9, 9, 10, false);
    });
    connect(ui->radioMedium, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) updateSpinBoxes(16, 16, 40, false);
    });
    connect(ui->radioExpert, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) updateSpinBoxes(16, 30, 99, false);
    });
    connect(ui->radioCustom, &QRadioButton::toggled, this, [this](bool checked) {
        updateSpinBoxes(ui->spinRows->value(), ui->spinCols->value(), ui->spinMines->value(), checked);
    });
}

GameSetupDialog::~GameSetupDialog() {
    delete ui;
}

void GameSetupDialog::updateSpinBoxes(int rows, int cols, int mines, bool enableCustom) {
    ui->spinRows->setValue(rows);
    ui->spinCols->setValue(cols);
    ui->spinMines->setValue(mines);

    ui->spinRows->setEnabled(enableCustom);
    ui->spinCols->setEnabled(enableCustom);
    ui->spinMines->setEnabled(enableCustom);
}

int GameSetupDialog::getRows() const { return ui->spinRows->value(); }
int GameSetupDialog::getCols() const { return ui->spinCols->value(); }
int GameSetupDialog::getMines() const { return ui->spinMines->value(); }

void GameSetupDialog::on_startButton_clicked() {
    accept();
}

void GameSetupDialog::on_cancelButton_clicked() {
    reject();
}