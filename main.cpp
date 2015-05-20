#include <QtWidgets/QApplication>
#include "main_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow ui;
    ui.show();
    return app.exec();
}
