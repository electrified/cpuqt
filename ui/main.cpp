#include <QtWidgets/QApplication>
#include <QImageReader>
#include "spdlog/spdlog.h"
#include "ui/main_window.h"

int main(int argc, char **argv) {
  auto console = spdlog::stdout_logger_mt("console");
  console->set_level(spdlog::level::debug);
  QApplication app(argc, argv);

  QCoreApplication::setOrganizationName("Badgersoft");
  QCoreApplication::setOrganizationDomain("maidavale.org");
  QCoreApplication::setApplicationName("Emu");

  /*
  QList<QByteArray> supportedImageFormats = QImageReader::supportedImageFormats();

  for (QByteArray ba : supportedImageFormats) {
    console->info() << ba.data();
  }*/

  MainWindow ui;
  ui.show();
  return app.exec();
}
