#include "config_tab.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

ConfigTab::ConfigTab(const QString &configName, ConfigManager *manager, QWidget *parent)
    : QWidget(parent), configName(configName), manager(manager)
{
    initUi();
    loadData();
}

void ConfigTab::initUi()
{
    auto *layout = new QVBoxLayout(this);
    layout->setSpacing(15);

    // Resolution
    auto *resLayout = new QHBoxLayout();
    auto *resLabel = new QLabel(tr("Resolution:"));
    resLabel->setFixedWidth(LABEL_WIDTH);
    resCombo = new QComboBox();
    resCombo->addItems({"100", "150", "200", "300", "400", "600", "1200", "2400", "4800", "9600"});
    resLayout->addWidget(resLabel);
    resLayout->addWidget(resCombo);
    layout->addLayout(resLayout);

    // Duplex
    auto *dupLayout = new QHBoxLayout();
    auto *dupLabel = new QLabel(tr("Duplex:"));
    dupLabel->setFixedWidth(LABEL_WIDTH);
    dupCombo = new QComboBox();
    dupCombo->addItems({"OFF", "ON"});
    dupLayout->addWidget(dupLabel);
    dupLayout->addWidget(dupCombo);
    layout->addLayout(dupLayout);

    // Size
    auto *sizeLayout = new QHBoxLayout();
    auto *sizeLabel = new QLabel(tr("Size:"));
    sizeLabel->setFixedWidth(LABEL_WIDTH);
    sizeCombo = new QComboBox();
    sizeCombo->addItems({"A4", "A3", "A5", "A6", "Letter", "Legal", "MAX"});
    sizeCombo->setEditable(true);
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(sizeCombo);
    layout->addLayout(sizeLayout);

    layout->addStretch();
}

void ConfigTab::loadData()
{
    Config data = manager->loadConfig(configName);
    resCombo->setCurrentText(data.resolution);
    dupCombo->setCurrentText(data.duplex);
    sizeCombo->setCurrentText(data.size);
}

Config ConfigTab::getData() const
{
    return Config{
        resCombo->currentText(),
        dupCombo->currentText(),
        sizeCombo->currentText()
    };
}
