cmake_minimum_required(VERSION 3.16)
project(brscan-skey-gui VERSION 0.1.0 LANGUAGES CXX)

# C++17 standard — supported by all modern Linux distros
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6 auto-processors
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6 Widgets
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Source files
set(SOURCES
    src/main.cpp
    src/config_manager.cpp
    src/config_tab.cpp
    src/main_window.cpp
)

set(HEADERS
    src/config_manager.h
    src/config_tab.h
    src/main_window.h
)

# Build executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

# Install rules
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES assets/brscan-skey-gui.desktop DESTINATION share/applications)

# ============================================================
# CPack — Generate .deb and .rpm packages
# ============================================================
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VENDOR "chainarong-ck")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GUI for Brother Scanner brscan-skey configuration")
set(CPACK_PACKAGE_CONTACT "chainarong-ck")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/chainarong-ck/brscan-skey-gui")

# .deb settings (Debian / Ubuntu)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt6widgets6 (>= 6.2)")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")

# .rpm settings (Fedora)
set(CPACK_RPM_PACKAGE_REQUIRES "qt6-qtbase >= 6.2")
set(CPACK_RPM_PACKAGE_LICENSE "GPL")

# Generators to produce
set(CPACK_GENERATOR "DEB;RPM")

include(CPack)
