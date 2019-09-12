TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += \
        main.cpp \
    clsopenmpi.cpp

unix:!macx: LIBS += -L$$PWD/../../../../test/software/openmpi/4.0.1/install/lib/ -lmpi

INCLUDEPATH += $$PWD/../../../../test/software/openmpi/4.0.1/install/include
DEPENDPATH += $$PWD/../../../../test/software/openmpi/4.0.1/install/include

HEADERS += \
    clsopenmpi.h
