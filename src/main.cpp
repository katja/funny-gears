#include <QApplication>

#include "main_window.h"

int main(int arg, char** argc) {
    QApplication app(arg, argc);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}