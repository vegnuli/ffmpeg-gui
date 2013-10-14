QT       += core gui

TARGET = ffmpeg-gui
TEMPLATE = app

CONFIG -= debug debug_and_release

SOURCES += src/main.cpp\
           src/ffmpegfrontend.cpp \
    src/settings.cpp \
    src/about.cpp

HEADERS  += src/ffmpegfrontend.h \
    src/settings.h \
    src/about.h

FORMS    += src/ffmpegfrontend.ui\
            src/ffmpegoutput.ui \
    src/about.ui

RESOURCES += src/resources.qrc

TRANSLATIONS = translations/ffmpeg-gui_it.ts \
    translations/ffmpeg-gui_ru.ts \
    translations/ffmpeg-gui_ua.ts \
    translations/ffmpeg-gui_de.ts

#debugging
message($$CONFIG)

CONFIG(debug) {
    DEFINES += DEBUGGING
    DEFINES += "PWD_PRO=$$PWD"
    CONFIG-=release
    message("Debug mode on. ffmpeg profiles files will be read also in "$$PWD"/ffmpeg-profiles")
}
CONFIG(release) {
    CONFIG-=debug
    message($$DEFINES)
    unix {
        message("Release mode on. ffmpeg profiles files will be read also in ~/.ffmpeg-gui/ffmpeg-profiles")
    }
    win32 {
        message("Release mode on. ffmpeg profiles files will be read also in ffmpeg-gui\\ffmpeg-profiles program folder")
    }
}
