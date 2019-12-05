#ifndef TETRA_GRIP_API_H
#define TETRA_GRIP_API_H

#include <QObject>
#include "Stim_includes/stim_gui_protocol.h"
#include "Stim_includes/stim_gui_protocol_rx.h"
#include "Stim_includes/stim_gui_protocol_tx.h"
#include "Stim_includes/uart.h"
#include "Stim_includes/clock.h"
#include "Stim_includes/debug.h"
#include "Stim_includes/sensor_message_format.h"
#include "Stim_includes/stim_gui_protocol_decode.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

#define _CRT_SECURE_NO_DEPRECATE

class tetra_grip_api : public QObject
{
    Q_OBJECT

public:
    explicit tetra_grip_api(QObject *parent = nullptr);

    void static send_config_file(QByteArray config, bool nonvolatile);
    void static send_long_register(uint8_t, uint32_t, uint8_t *);
    void static clear_stim_config(void);
    bool static send_short_block(STIM_GUI_MESSAGE_S_BLOCK_T *pblock);
    void static read_stim_status_reg(void);
    void static battery_percentage(void);


     QSerialPort *serial = nullptr;
     QString comPortName;


signals:

     void tetraGripEvent(STIM_GUI_TOPIC_T topic, uint8_t reg, uint32_t value);


public slots:

     void openSerialPort();
     void closeSerialPort();
     void readData();


private:

};

extern tetra_grip_api api;

#endif // TETRA_GRIP_API_H
