#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class CellButton : public QPushButton {
    Q_OBJECT

public:
    CellButton(int r, int c, QWidget* parent = nullptr);
    void setMinesCount(int count);
    int getRow() const { return row; }
    int getCol() const { return col; }

signals:
    void leftClicked();
    void rightClicked();

protected:
    void mousePressEvent(QMouseEvent* e) override;

private:
    int row;
    int col;
};

#endif