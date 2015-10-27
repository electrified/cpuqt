#include <QtWidgets/QApplication>
#include <QImageReader>
#include <iostream>

#include "ui/main_window.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    QCoreApplication::setOrganizationName("Badgersoft");
    QCoreApplication::setOrganizationDomain("maidavale.org");
    QCoreApplication::setApplicationName("Emu");
    
    QList<QByteArray> supportedImageFormats = QImageReader::supportedImageFormats();

    for (QByteArray ba : supportedImageFormats) {
        std::cout << ba.data() << std::endl;
    }

    MainWindow ui;
    ui.show();
    return app.exec();

}
