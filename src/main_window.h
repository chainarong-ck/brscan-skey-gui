#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMap>
#include "config_manager.h"

class ConfigTab;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void saveAll();

private:
    void initUi();

    ConfigManager manager;
    QMap<QString, ConfigTab*> tabWidgets;
};

#endif // MAIN_WINDOW_H
