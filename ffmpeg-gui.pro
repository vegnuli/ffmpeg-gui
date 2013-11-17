QT += core \
    gui
TARGET = ffmpeg-gui
VERSION = 1.2
TEMPLATE = app
DEFINES += APP_VERSION="$$VERSION"
DEPENDPATH += . translations
CONFIG -= debug \
    debug_and_release
SOURCES += src/main.cpp \
    src/ffmpegfrontend.cpp \
    src/settings.cpp \
    src/about.cpp
HEADERS += src/ffmpegfrontend.h \
    src/settings.h \
    src/about.h
FORMS += src/ffmpegfrontend.ui \
    src/ffmpegoutput.ui \
    src/about.ui
RESOURCES += resources.qrc
TRANSLATIONS = translations/ffmpeg-gui_it.ts \
    translations/ffmpeg-gui_ru.ts \
    translations/ffmpeg-gui_ua.ts \
    translations/ffmpeg-gui_es.ts \
    translations/ffmpeg-gui_es_VE.ts \
    translations/ffmpeg-gui_de.ts
CODECFORTR = UTF-8
CODECFORSRC = UTF-8
#include(translations/locale.pri)


# debugging
message($$CONFIG)
CONFIG(debug) { 
    DEFINES += DEBUGGING
    DEFINES += "PWD_PRO=$$PWD"
    CONFIG -= release
    message("Debug mode on. ffmpeg profiles files will be read also in "$$PWD"/ffmpeg-profiles")
}
CONFIG(release) { 
    CONFIG -= debug
    message($$DEFINES)
    unix:message("Release mode on. ffmpeg profiles files will be read also in ~/.ffmpeg-gui/ffmpeg-profiles")
}

# install featuresby PICCORO je je

isEmpty(PREFIX):PREFIX = $$DESTDIR/usr
BINDIR = $$PREFIX/bin
DATADIR = $$PREFIX/share
# we only have presets for data, so use same as ffmpeg
PKGDATADIR = $$DATADIR/ffmpeg
DEFINES += DATADIR=\\\"$$DATADIR\\\" \
    PKGDATADIR=\\\"$$PKGDATADIR\\\" \
    PKGVERSION=\\\"$$VERSION\\\"

INSTALLS += target translations desktop
target.path = $$BINDIR

translations.path = $$DATADIR/ffmpeg-gui
translations.files += translations/ffmpeg-gui_it.qm \
    translations/ffmpeg-gui_ru.qm \
    translations/ffmpeg-gui_ua.qm \
    translations/ffmpeg-gui_es.qm \
    translations/ffmpeg-gui_es_VE.qm \
    translations/ffmpeg-gui_de.qm

desktop.files = ffmpeg-gui.desktop 
desktop.path = $$DATADIR/applications

