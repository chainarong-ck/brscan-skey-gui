#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <QString>
#include <QMap>
#include <QDir>

struct Config {
    QString resolution;
    QString duplex;
    QString size;
};

class ConfigManager {
public:
    ConfigManager();

    static const QMap<QString, QString>& configFiles();
    Config loadConfig(const QString &configName) const;
    void saveConfig(const QString &configName, const Config &data) const;

private:
    QDir configDir;
    static const Config DEFAULTS;

    void ensureConfigDir();
    void writeDefaultConfig(const QString &path) const;
    QString buildConfigContent(const Config &cfg) const;
};

#endif // CONFIG_MANAGER_H
