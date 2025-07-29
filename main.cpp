#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Калькулятор p-ичных чисел");
    w.setWindowIcon(QIcon(":images/pic/icon.png"));
    w.show();
    return a.exec();
}
