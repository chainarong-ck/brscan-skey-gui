#ifndef CONFIG_TAB_H
#define CONFIG_TAB_H

#include <QWidget>
#include <QComboBox>
#include "config_manager.h"

class ConfigTab : public QWidget {
    Q_OBJECT

public:
    explicit ConfigTab(const QString &configName, ConfigManager *manager, QWidget *parent = nullptr);
    Config getData() const;

private:
    void initUi();
    void loadData();

    QString configName;
    ConfigManager *manager;

    QComboBox *resCombo;
    QComboBox *dupCombo;
    QComboBox *sizeCombo;

    static constexpr int LABEL_WIDTH = 80;
};

#endif // CONFIG_TAB_H
