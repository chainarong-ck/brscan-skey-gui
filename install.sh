#!/bin/bash

# Configuration
APP_NAME="brscan-skey-gui"
APP_TITLE="Brother Scanner Config"
ICON_NAME="scanner"  # Default icon, or we can use a custom one if available
EXEC_NAME="brscan-skey-gui"
INSTALL_DIR="$HOME/.local/share/$APP_NAME"
DESKTOP_FILE_DIR="$HOME/.local/share/applications"
BIN_DIR="$HOME/.local/bin"

# Centers text
print_centered() {
    term_width=$(tput cols)
    text="$1"
    padding=$(( (term_width - ${#text}) / 2 ))
    printf "%${padding}s%s\n" "" "$text"
}

# Colors
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

clear
print_centered "========================================"
print_centered "   BRScan SKey GUI Installer   "
print_centered "========================================"
echo ""

# Detect OS
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
    VERSION_ID=$VERSION_ID
else
    echo -e "${RED}Cannot detect OS. Exiting.${NC}"
    exit 1
fi

echo -e "Detected OS: ${GREEN}$NAME ($OS)${NC}"
echo ""

# Function to install system dependencies
install_system_deps() {
    echo -e "${YELLOW}Installing system dependencies...${NC}"
    
    case $OS in
        debian)
            sudo apt update
            # Debian 13+ has these packages
            if sudo apt install -y python3-pyside6.qtcore python3-pyside6.qtwidgets python3-venv; then
                USE_SYSTEM_PACKAGES=true
            else
                echo -e "${YELLOW}System packages not found, falling back to venv...${NC}"
                sudo apt install -y python3-pip python3-venv
                USE_SYSTEM_PACKAGES=false
            fi
            ;;
        ubuntu|linuxmint|pop)
            sudo apt update
            # Ubuntu 24.04 often misses these, will likely fallback
            if sudo apt install -y python3-pyside6.qtcore python3-pyside6.qtwidgets; then
                USE_SYSTEM_PACKAGES=true
            else
                echo -e "${YELLOW}System packages not found (common on Ubuntu 24.04), falling back to venv...${NC}"
                sudo apt install -y python3-pip python3-venv python3-full
                USE_SYSTEM_PACKAGES=false
            fi
            ;;
        fedora)
            sudo dnf install -y python3-pyside6
            USE_SYSTEM_PACKAGES=true
            ;;
        arch|manjaro)
            sudo pacman -S --noconfirm pyside6
            USE_SYSTEM_PACKAGES=true
            ;;
        *)
            echo -e "${YELLOW}Unsupported OS for automatic system package installation.${NC}"
            echo -e "We will try to install via pip in a virtual environment."
            USE_SYSTEM_PACKAGES=false
            ;;
    esac
}

# Install
install_system_deps

echo ""
echo -e "${YELLOW}Setting up application...${NC}"

# Create Install Directory
mkdir -p "$INSTALL_DIR"
cp -r src "$INSTALL_DIR/"
cp pyproject.toml "$INSTALL_DIR/"

# Setup Python Environment
if [ "$USE_SYSTEM_PACKAGES" = true ]; then
    echo -e "Using system Python packages."
    PYTHON_EXEC="/usr/bin/python3"
    # Create simple wrapper script
    mkdir -p "$BIN_DIR"
    echo "#!/bin/bash" > "$BIN_DIR/$EXEC_NAME"
    echo "cd $INSTALL_DIR" >> "$BIN_DIR/$EXEC_NAME"
    echo "export QT_QPA_PLATFORM_THEME=qt6ct" >> "$BIN_DIR/$EXEC_NAME" # Attempt to fix theme
    echo "$PYTHON_EXEC src/main.py \"\$@\"" >> "$BIN_DIR/$EXEC_NAME"
    chmod +x "$BIN_DIR/$EXEC_NAME"
else
    echo -e "Setting up virtual environment in $INSTALL_DIR/.venv..."
    python3 -m venv "$INSTALL_DIR/.venv"
    source "$INSTALL_DIR/.venv/bin/activate"
    
    echo -e "Installing PySide6 via pip..."
    pip install pyside6
    
    PYTHON_EXEC="$INSTALL_DIR/.venv/bin/python3"
    
    # Create wrapper script using venv
    mkdir -p "$BIN_DIR"
    echo "#!/bin/bash" > "$BIN_DIR/$EXEC_NAME"
    echo "cd $INSTALL_DIR" >> "$BIN_DIR/$EXEC_NAME"
    echo "$PYTHON_EXEC src/main.py \"\$@\"" >> "$BIN_DIR/$EXEC_NAME"
    chmod +x "$BIN_DIR/$EXEC_NAME"
fi

# Create Desktop Entry
echo -e "${YELLOW}Creating Desktop Shortcut...${NC}"
mkdir -p "$DESKTOP_FILE_DIR"
cat > "$DESKTOP_FILE_DIR/$APP_NAME.desktop" <<EOF
[Desktop Entry]
Name=$APP_TITLE
Comment=GUI for Brother Scanner Configuration
Exec=$BIN_DIR/$EXEC_NAME
Icon=scanner
Terminal=false
Type=Application
Categories=Utility;Settings;System;
Keywords=Scanner;Brother;Config;
EOF

# Make sure local bin is in path (warn user if not)
if [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
    echo ""
    echo -e "${YELLOW}WARNING: $HOME/.local/bin is not in your PATH.${NC}"
    echo "You may need to log out and log back in, or add it to your shell configuration."
fi

echo ""
echo -e "${GREEN}========================================"
echo -e "   Installation Complete!   "
echo -e "========================================${NC}"
echo "You can launch the app by searching for '$APP_TITLE' in your menu"
echo "or by running '$EXEC_NAME' in your terminal."
echo ""
