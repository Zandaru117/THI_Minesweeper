#include "mainwindow.h"
#include "gamecontroller.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    GameController controller(&w);
    w.setController(&controller);

    w.show();

    controller.startNewGame(9, 9, 10);

    return a.exec();
}