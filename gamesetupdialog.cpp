#include "gamesetupdialog.h"
#include "ui_gamesetupdialog.h"

GameSetupDialog::GameSetupDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::GameSetupDialog)
{
    ui->setupUi(this);

    ui->spinRows->setRange(8, 32);
    ui->spinCols->setRange(8, 60);

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

    connect(ui->spinRows, QOverload<int>::of(&QSpinBox::valueChanged), this, &GameSetupDialog::updateMaxMines);
    connect(ui->spinCols, QOverload<int>::of(&QSpinBox::valueChanged), this, &GameSetupDialog::updateMaxMines);

    ui->radioNovice->setChecked(true);
    updateMaxMines();
}

GameSetupDialog::~GameSetupDialog() {
    delete ui;
}

void GameSetupDialog::updateMaxMines() {
    if (ui->radioCustom->isChecked()) {
        int r = ui->spinRows->value();
        int c = ui->spinCols->value();
        int totalCells = r * c;

        // Плотность не более 30%
        int maxMines = static_cast<int>(totalCells * 0.30);
        if (maxMines < 1) maxMines = 1;

        ui->spinMines->setRange(1, maxMines);
    } else {
        ui->spinMines->setRange(1, 500);
    }
}

void GameSetupDialog::updateSpinBoxes(int rows, int cols, int mines, bool enableCustom) {
    ui->spinRows->setValue(rows);
    ui->spinCols->setValue(cols);

    // Сначала настраиваем лимиты в зависимости от режима, затем ставим значение мин
    updateMaxMines();
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