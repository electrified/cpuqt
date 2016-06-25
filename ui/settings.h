#pragma once
#include <QString>
#include <QSettings>
#include <list>

class Settings {
  QSettings* settings;
public:
    Settings();
    void update_recents_list(QString list_name, QString rom_path);
    std::list<QString> get_recents_list(QString list_name);
    const QString recent_roms = QString("recentroms");
    const QString recent_scripts = QString("recentscripts");
};


