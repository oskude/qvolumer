QT += core gui widgets
TARGET = qvolumer
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
	main.cpp \
	volume-splash.cpp

HEADERS += \
	volume-splash.h

include(../vendor/vendor.pri)
