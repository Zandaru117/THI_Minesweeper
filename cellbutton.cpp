#include "cellbutton.h"

CellButton::CellButton(int r, int c, QWidget* parent)
    : QPushButton(parent), row(r), col(c) {

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