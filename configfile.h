#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QIODevice>
#include <QSettings>

class ConfigFile
{
public:
    bool debug;

    static ConfigFile* getInstance();
    bool LoadConfig(const QString &conf);
    ~ConfigFile();

    QString get(const QString &key);

private:
    static ConfigFile* instance;
    ConfigFile() : isInited(false){};
    bool isInited;
    QSettings *settings;
    static bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map);
    static bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map);
};

extern ConfigFile *cfg;

#endif // CONFIGFILE_H
