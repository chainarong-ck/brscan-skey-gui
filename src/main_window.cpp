#include "main_window.h"
#include "config_tab.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Brscan-Skey Configuration"));
    resize(450, 300);
    initUi();
}

void MainWindow::initUi()
{
    // Main widget
    auto *mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    auto *mainLayout = new QVBoxLayout(mainWidget);

    // Title / Header
    auto *title = new QLabel(tr("Brother Scanner Key Configuration"));
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    title->setFont(titleFont);
    mainLayout->addWidget(title);

    // Tabs
    auto *tabs = new QTabWidget();
    const auto &configFiles = ConfigManager::configFiles();
    for (auto it = configFiles.cbegin(); it != configFiles.cend(); ++it) {
        auto *tab = new ConfigTab(it.key(), &manager, this);
        tabs->addTab(tab, it.key());
        tabWidgets[it.key()] = tab;
    }
    mainLayout->addWidget(tabs);

    // Buttons
    auto *saveBtn = new QPushButton(tr("Save All Settings"));
    saveBtn->setCursor(Qt::PointingHandCursor);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveAll);

    auto *cancelBtn = new QPushButton(tr("Close"));
    cancelBtn->setCursor(Qt::PointingHandCursor);
    connect(cancelBtn, &QPushButton::clicked, this, &MainWindow::close);

    // Button layout (Horizontal)
    auto *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);

    mainLayout->addLayout(btnLayout);
}

void MainWindow::saveAll()
{
    try {
        for (auto it = tabWidgets.cbegin(); it != tabWidgets.cend(); ++it) {
            Config config = it.value()->getData();
            manager.saveConfig(it.key(), config);
        }
        QMessageBox::information(this, tr("Success"), tr("Configuration saved successfully!"));
    } catch (const std::exception &e) {
        QMessageBox::critical(this, tr("Error"),
            tr("Failed to save configuration: %1").arg(e.what()));
    }
}
