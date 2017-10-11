QT += core gui widgets quickwidgets
TARGET = qvolumer
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	main.cpp \
	volume-splash.cpp \
	pulse-audio.cpp

HEADERS += \
	volume-splash.h \
	pulse-audio.h

RESOURCES += \
	files.qrc

include(../vendor/vendor.pri)
