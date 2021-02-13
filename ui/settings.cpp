#include "settings.h"
#include "spdlog/spdlog.h"

Settings::Settings() {
  settings = new QSettings();
}

void Settings::update_recents_list(QString list_name, QString rom_path) {

  int size = settings->beginReadArray(list_name);

  bool found = false;

  for (int i = 0; i < size; i++) {
    settings->setArrayIndex(i);
    QString existing_path = settings->value("path").toString();
    if (existing_path == rom_path) {
      found = true;
    }
  }
  settings->endArray();

  if (!found) {
    settings->beginWriteArray(list_name);
    settings->setArrayIndex(size);
    settings->setValue("path", rom_path);
    settings->endArray();
    settings->sync();
  }
}

std::list<QString> Settings::get_recents_list(QString list_name) {
  std::list<QString> recentFiles;
  
  spdlog::get("general")->debug(settings->fileName().toStdString());
  int size = settings->beginReadArray(list_name);
//   std::cout << "reading vals from config file " << size << std::endl;
  for (int i = 0; i < size; ++i) {
    settings->setArrayIndex(i);
    recentFiles.push_back(settings->value("path").toString());
  }
  settings->endArray();
  return recentFiles;
}
