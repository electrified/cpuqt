#include <QtWidgets/QApplication>
#include <QImageReader>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "ui/main_window.h"

int main(int argc, char **argv) {
  auto console = spdlog::stdout_color_mt("console");
  console->set_level(spdlog::level::debug);
  QApplication app(argc, argv);

  QCoreApplication::setOrganizationName("Badgersoft");
  QCoreApplication::setOrganizationDomain("maidavale.org");
  QCoreApplication::setApplicationName("Emu");

  MainWindow ui;
  ui.show();
  return app.exec();
}
