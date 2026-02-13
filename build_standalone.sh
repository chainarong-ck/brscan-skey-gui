#!/bin/bash

APP_NAME="brscan-skey-gui"
MAIN_SCRIPT="src/main.py"

echo "========================================"
echo "   Building Standalone Executable"
echo "========================================"

# Check if uv is installed
if ! command -v uv &> /dev/null; then
    echo "uv not found. Please install uv first."
    exit 1
fi

# Clean previous builds
rm -rf build dist

# Build using PyInstaller through uv
echo "Building..."
uv run pyinstaller --name "$APP_NAME" \
            --onefile \
            --windowed \
            --clean \
            --add-data "src:src" \
            "$MAIN_SCRIPT"

echo ""
echo "Build Complete!"
echo "executable is located at: dist/$APP_NAME"
echo ""
echo "You can now distribute 'dist/$APP_NAME' to other Linux users."
echo "(Note: They must have glibc version >= your system's version)"
