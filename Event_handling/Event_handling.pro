QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Stim_includes/crc32.c \
    Stim_includes/stim_gui_protocol.c \
    Stim_includes/stim_gui_protocol_decode.c \
    Stim_includes/stim_gui_protocol_rx.c \
    Stim_includes/stim_gui_protocol_tx.c \
    main.cpp \
    patients.cpp \
    qcustomplot.cpp \
    settings.cpp \
    tetra_grip_api.cpp \
    tetra_grip_reporter.cpp \
    tetra_grip_writer.cpp

HEADERS += \
    Stim_includes/clock.h \
    Stim_includes/crc32.h \
    Stim_includes/debug.h \
    Stim_includes/hardware.h \
    Stim_includes/sensor_message_format.h \
    Stim_includes/stim_engine.h \
    Stim_includes/stim_gui_protocol.h \
    Stim_includes/stim_gui_protocol_decode.h \
    Stim_includes/stim_gui_protocol_rx.h \
    Stim_includes/stim_gui_protocol_tx.h \
    Stim_includes/stim_regs.h \
    Stim_includes/system_config.h \
    Stim_includes/system_definitions.h \
    Stim_includes/uart.h \
    patients.h \
    qcustomplot.h \
    settings.h \
    tetra_grip_api.h \
    tetra_grip_reporter.h \
    tetra_grip_writer.h

FORMS += \
    patients.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
