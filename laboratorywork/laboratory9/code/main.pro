include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

INCLUDEPATH +=..\Lab9_Project_for_tests

HEADERS += \
        ../Lab9_Project_for_tests/IKeypad.h \
        ../Lab9_Project_for_tests/ILatch.h \
        ../Lab9_Project_for_tests/lockcontroller.h \
        tst_testlab9.h

SOURCES += \
        ../Lab9_Project_for_tests/lockcontroller.cpp \
        main.cpp
