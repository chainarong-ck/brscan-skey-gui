#include "config_manager.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <stdexcept>

const Config ConfigManager::DEFAULTS = {"100", "OFF", "A4"};

ConfigManager::ConfigManager()
    : configDir(QDir::homePath() + "/.brscan-skey")
{
    ensureConfigDir();
}

const QMap<QString, QString>& ConfigManager::configFiles()
{
    static const QMap<QString, QString> files = {
        {"Scan to File",  "scantofile.config"},
        {"Scan to Email", "scantoemail.config"},
        {"Scan to Image", "scantoimage.config"},
        {"Scan to OCR",   "scantoocr.config"}
    };
    return files;
}

void ConfigManager::ensureConfigDir()
{
    if (!configDir.exists()) {
        configDir.mkpath(".");
    }

    const auto &files = configFiles();
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        QString path = configDir.filePath(it.value());
        if (!QFile::exists(path)) {
            writeDefaultConfig(path);
        }
    }
}

void ConfigManager::writeDefaultConfig(const QString &path) const
{
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << buildConfigContent(DEFAULTS);
        file.close();
    }
}

QString ConfigManager::buildConfigContent(const Config &cfg) const
{
    return QStringLiteral(
        "#[brscan-skey]\n\n"
        "# resolution=100,150,200,300,400,600,1200,2400,4800,9600\n"
        "resolution=%1\n\n"
        "#duplex=OFF,ON\n"
        "duplex=%2\n\n"
        "#size=MAX,A3,A4,A5,A6,Letter,Legal,${width}x${height} (mm)\n"
        "size=%3\n"
    ).arg(cfg.resolution, cfg.duplex, cfg.size);
}

Config ConfigManager::loadConfig(const QString &configName) const
{
    const auto &files = configFiles();
    if (!files.contains(configName)) {
        throw std::runtime_error("Unknown config: " + configName.toStdString());
    }

    QString path = configDir.filePath(files[configName]);
    QMap<QString, QString> configData;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return DEFAULTS;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith('#')) {
            continue;
        }
        int eqPos = line.indexOf('=');
        if (eqPos != -1) {
            QString key = line.left(eqPos).trimmed();
            QString value = line.mid(eqPos + 1).trimmed();
            configData[key] = value;
        }
    }
    file.close();

    return Config{
        configData.value("resolution", DEFAULTS.resolution),
        configData.value("duplex", DEFAULTS.duplex),
        configData.value("size", DEFAULTS.size)
    };
}

void ConfigManager::saveConfig(const QString &configName, const Config &data) const
{
    const auto &files = configFiles();
    if (!files.contains(configName)) {
        throw std::runtime_error("Unknown config: " + configName.toStdString());
    }

    QString path = configDir.filePath(files[configName]);
    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << buildConfigContent(data);
        file.close();
    }
}
