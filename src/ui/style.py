
def get_stylesheet():
    return """
    QTabWidget::pane {
        border: 1px solid #333;
        background: #242424;
        border-radius: 8px;
        top: -1px;
    }

    QTabBar::tab {
        background: #2d2d2d;
        color: #888;
        padding: 8px 16px;
        margin-right: 4px;
        border-top-left-radius: 6px;
        border-top-right-radius: 6px;
    }

    QTabBar::tab:selected {
        background: #242424;
        color: #3d8af7;
        border-bottom: 2px solid #3d8af7;
    }

    QTabBar::tab:hover:!selected {
        background: #353535;
        color: #bbb;
    }

    QLabel {
        color: #e0e0e0;
        font-weight: 500;
    }

    QComboBox {
        background-color: #333;
        border: 1px solid #444;
        border-radius: 4px;
        padding: 4px 8px;
        color: #e0e0e0;
        min-height: 24px;
    }

    QComboBox:hover {
        border: 1px solid #3d8af7;
    }

    QComboBox::drop-down {
        border: none;
        width: 20px;
    }

    QPushButton {
        background-color: #3d8af7;
        color: white;
        border: none;
        border-radius: 6px;
        padding: 8px 20px;
        font-weight: 600;
        min-width: 80px;
    }

    QPushButton:hover {
        background-color: #559aff;
    }

    QPushButton:pressed {
        background-color: #2a6ecb;
    }

    QPushButton#closeButton {
        background-color: transparent;
        border: 1px solid #444;
        color: #888;
    }

    QPushButton#closeButton:hover {
        background-color: #333;
        color: #e0e0e0;
    }
    """
