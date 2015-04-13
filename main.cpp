#include <QtWidgets/QApplication>
#include "cpuqt2.h"
#include "MainWindow.h"
#include <boost/algorithm/string.hpp>
#include <vector>

int main(int argc, char** argv)
{

    std::vector<std::string> strs;
    boost::split(strs, "string to split", boost::is_any_of("\t "));


    QApplication app(argc, argv);
    QMainWindow* mw = new QMainWindow();
    Ui::MainWindow ui;
    ui.setupUi(mw);
    mw->show();
    return app.exec();
}
