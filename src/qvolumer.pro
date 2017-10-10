QT += core gui widgets
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

include(../vendor/vendor.pri)
