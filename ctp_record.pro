#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T14:42:40
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = ctp_record
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ctp_quote.cpp \
    ctp_quote_qthread.cpp \
    ctp_manager.cpp \
    ctp_log.cpp \
    ../gpp_qt/cfg/cfg.cpp \
    ../gpp_qt/log_info/log_info.cpp \
    ../gpp_qt/wfunction/wfunction.cpp \
	../gpp_qt/wfunction/udp_sender.cpp \
	../gpp_qt/cmd_line/cmd_line.cpp

HEADERS += \
    ctp_quote.h \
    ctp_quote_qthread.h \
    ctp_manager.h \
    ctp_log.h \
    ../gpp_qt/cfg/cfg.h \
    ../gpp_qt/log_info/log_info.h \
    ../gpp_qt/wfunction/wfunction.h \
	../gpp_qt/wfunction/udp_sender.h \
	../gpp_qt/cmd_line/cmd_line.h

win32: LIBS += -L$$PWD/../libs/ctp/ -lthostmduserapi

INCLUDEPATH += $$PWD/../libs/ctp
DEPENDPATH += $$PWD/../libs/ctp
