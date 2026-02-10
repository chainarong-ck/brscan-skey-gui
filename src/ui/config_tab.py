from PySide6.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QLabel, QComboBox, QSpacerItem, QSizePolicy
from core.config_manager import ConfigManager, Config

class ConfigTab(QWidget):
    LABEL_WIDTH = 80

    def __init__(self, config_name: str, manager: ConfigManager) -> None:
        """Initialize the configuration tab."""
        super().__init__()
        self.config_name: str = config_name
        self.manager: ConfigManager = manager
        self.init_ui()
        self.load_data()

    def init_ui(self) -> None:
        """Initialize the user interface."""
        # Config layout
        layout: QVBoxLayout = QVBoxLayout()
        layout.setSpacing(15)
        self.setLayout(layout)
        
        # Resolution
        res_layout: QHBoxLayout = QHBoxLayout()
        res_label: QLabel = QLabel("Resolution:")
        res_label.setFixedWidth(self.LABEL_WIDTH)
        self.res_combo: QComboBox = QComboBox()
        self.res_combo.addItems(["100", "150", "200", "300", "400", "600", "1200", "2400", "4800", "9600"])
        res_layout.addWidget(res_label)
        res_layout.addWidget(self.res_combo)
        layout.addLayout(res_layout)

        # Duplex
        dup_layout: QHBoxLayout = QHBoxLayout()
        dup_label: QLabel = QLabel("Duplex:")
        dup_label.setFixedWidth(self.LABEL_WIDTH)
        self.dup_combo: QComboBox = QComboBox()
        self.dup_combo.addItems(["OFF", "ON"])
        dup_layout.addWidget(dup_label)
        dup_layout.addWidget(self.dup_combo)
        layout.addLayout(dup_layout)

        # Size
        size_layout: QHBoxLayout = QHBoxLayout()
        size_label: QLabel = QLabel("Size:")
        size_label.setFixedWidth(self.LABEL_WIDTH)
        self.size_combo: QComboBox = QComboBox()
        self.size_combo.addItems(["A4", "A3", "A5", "A6", "Letter", "Legal", "MAX"])
        self.size_combo.setEditable(True)
        size_layout.addWidget(size_label)
        size_layout.addWidget(self.size_combo)
        layout.addLayout(size_layout)

        layout.addStretch()

    def load_data(self) -> None:
        """Load configuration data."""
        data: Config = self.manager.load_config(self.config_name)
        self.res_combo.setCurrentText(data.resolution)
        self.dup_combo.setCurrentText(data.duplex)
        self.size_combo.setCurrentText(data.size)

    def get_data(self) -> Config:
        """Get configuration data."""
        return Config(
            resolution=self.res_combo.currentText(),
            duplex=self.dup_combo.currentText(),
            size=self.size_combo.currentText()
        )
