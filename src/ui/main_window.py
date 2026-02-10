from PySide6.QtWidgets import QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QTabWidget, QLabel, QPushButton, QMessageBox
from PySide6.QtCore import Qt
from core.config_manager import ConfigManager, Config
from ui.config_tab import ConfigTab

class MainWindow(QMainWindow):
    def __init__(self) -> None:
        """Initialize the main window."""
        super().__init__()
        self.setWindowTitle("Brscan-Skey Configuration")
        self.resize(450, 300)
        self.manager: ConfigManager = ConfigManager()

        # Initialize UI
        self.init_ui()

    def init_ui(self) -> None:
        """Initialize the user interface."""
        # Main widget
        main_widget: QWidget = QWidget()
        self.setCentralWidget(main_widget)

        # Set layout for main widget (Vertical)
        main_layout: QVBoxLayout = QVBoxLayout()
        main_widget.setLayout(main_layout)

        # Title / Header
        title: QLabel = QLabel("Brother Scanner Key Configuration")
        title.setAlignment(Qt.AlignCenter)
        title.font().setPointSize(14)
        title.font().setBold(True)
        main_layout.addWidget(title)

        # Tabs
        tabs: QTabWidget = QTabWidget()
        self.tab_widgets: dict[str, ConfigTab] = {}
        for config_name, config_file in self.manager.CONFIG_FILES.items():
            tab: ConfigTab = ConfigTab(config_name, self.manager)
            tabs.addTab(tab, config_name)
            self.tab_widgets[config_name] = tab
        main_layout.addWidget(tabs)

        # Buttons
        save_btn: QPushButton = QPushButton("Save All Settings")
        save_btn.clicked.connect(self.save_all)
        save_btn.setCursor(Qt.PointingHandCursor)
        
        cancel_btn: QPushButton = QPushButton("Close")
        cancel_btn.setObjectName("closeButton")
        cancel_btn.clicked.connect(self.close)
        cancel_btn.setCursor(Qt.PointingHandCursor)

        # Buttons layout (Horizontal)
        btn_layout: QHBoxLayout = QHBoxLayout()
        btn_layout.addStretch()
        btn_layout.addWidget(save_btn)
        btn_layout.addWidget(cancel_btn)
        
        # Add buttons to main layout
        main_layout.addLayout(btn_layout)

    def save_all(self) -> None:
        """Save all configurations action."""
        try:
            for config_name, widget in self.tab_widgets.items():
                config: Config = widget.get_data()
                self.manager.save_config(config_name, config)
            QMessageBox.information(self, "Success", "Configuration saved successfully!")
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to save configuration: {e}")

