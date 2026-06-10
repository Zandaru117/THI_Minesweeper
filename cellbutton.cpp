#include "cellbutton.h"
#include <QMouseEvent>

// Вспомогательная функция (статическая в рамках файла)
static QString getNumberColor(int minesCount) {
    switch (minesCount) {
    case 1: return "#1565C0"; // Яркий синий
    case 2: return "#2E7D32"; // Насыщенный зеленый
    case 3: return "#C62828"; // Насыщенный красный
    case 4: return "#283593"; // Темно-синий
    case 5: return "#6A1B9A"; // Пурпурный
    case 6: return "#00838F"; // Бирюзовый
    case 7: return "#000000"; // Черный
    case 8: return "#37474F"; // Серый
    default: return "#000000";
    }
}

CellButton::CellButton(int r, int c, QWidget* parent)
    : QPushButton(parent), row(r), col(c)
{
    setFixedSize(30, 30);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void CellButton::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        emit leftClicked();
    }
    else if (e->button() == Qt::RightButton) {
        emit rightClicked();
    }
    e->accept();
}

void CellButton::setMinesCount(int count) {
    if (count > 0) {
        this->setText(QString::number(count));
        QString color = getNumberColor(count);

        this->setStyleSheet(QString(
                                "QPushButton {"
                                "   color: %1;"
                                "   font-weight: bold;"
                                "   font-size: 14px;"
                                "   background-color: #E0E0E0;"
                                "   border: 1px solid #B0B0B0;"
                                "}"
                                ).arg(color));
    }
    else {
        this->setText("");
        this->setStyleSheet(
            "QPushButton {"
            "   background-color: #E0E0E0;"
            "   border: 1px solid #B0B0B0;"
            "}"
            );
    }
}