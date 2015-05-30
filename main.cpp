#include <QtWidgets/QApplication>
#include "ui/main_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    QCoreApplication::setOrganizationName("Badgersoft");
    QCoreApplication::setOrganizationDomain("maidavale.org");
    QCoreApplication::setApplicationName("Emu");
    
    MainWindow ui;
    ui.show();
    return app.exec();
}
