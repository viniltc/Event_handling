#include "tetra_grip_api.h"
#include "tetra_grip_reporter.h"
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


#define _CRT_SECURE_NO_DEPRECATE

using namespace::std;

tetra_grip_api::tetra_grip_api(QObject *parent) : QObject(parent)
{


}

void tetra_grip_api::openSerialPort()//Vendor Identifier: 403 , Product Identifier: 6015
{
    serial = new QSerialPort();

    QList <QSerialPortInfo>stim;
    QSerialPortInfo info;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
       if(info.description() == "USB Serial Port" && info.manufacturer() == "FTDI" && QString::number(info.vendorIdentifier(), 16)== "403" && QString::number(info.productIdentifier(), 16)== "6015")
        {
           comPortName = info.portName();
        }
    }
    //serial->setPortName("com5");
    serial->setPortName(comPortName);
    serial->setBaudRate(1000000);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::HardwareControl);
    if(serial->open(QIODevice::ReadWrite))
    {
        qDebug()<<"Open port OK";
    }
    else
    {
        qDebug()<<"Failed to open port. Error code: "<< serial->error() << serial->errorString();
    }


}

void tetra_grip_api::readData()
{


   const QByteArray data = api.serial->readAll();
       qDebug()<<"\n---------------------------------\n";
       qDebug()<<"Bytes read len"<< data.length();
       qDebug()<<"\n Bytes data " << data.toHex();


    STIM_GUI_PROTOCOL_Process_Received_Bytes((uint8_t*)data.data(), (size_t)data.length());

}


void tetra_grip_api::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();

}
void tetra_grip_api::send_long_register(uint8_t reg, uint32_t data_len, uint8_t *data)

{


    STIM_GUI_MESSAGE_L_BLOCK_T block={};

    if(!data)
    {
        printf("Error: null pointer argument to send_long_register().\n");
        return;
    }

    block.msg_type=WRITE_COMMAND;
    block.reg_address=reg;
    block.data_length=data_len;
    block.data=data;
    printf("Writing %d bytes to long register %d: '%*s'...\n", data_len, reg, data_len, data);


    if(STIM_GUI_Send_long_message(STIMULATOR_ADDRESS1, GUI_ADDRESS, &block))
    {
        printf("Write OK\n");
    }
    else
    {
        printf("Write Failed.\n");
    }
}

void tetra_grip_api::send_config_file(QByteArray config, bool nonvolatile)

{
      //  clear_stim_config(); >>>>>>>>>>>   check this

        if(config.length())
        {
            send_long_register((nonvolatile?STIM_LONG_REG_NV_STIM_CONFIG_FILE:STIM_LONG_REG_STIM_CONFIG_FILE), config.length(),(uint8_t *)config.data());
        }
        else
        {
            printf("Could not read any bytes from file.\n");
        }

}

void tetra_grip_api::clear_stim_config(void)
{
    STIM_GUI_MESSAGE_S_BLOCK_T block={};

    uint8_t command=STIM_COMMAND_CLEAR_STIM_CONFIG;

    block.msg_type=WRITE_COMMAND;
    block.topic=TOPIC_STIMULATOR;
    block.index=0;
    block.reg_address=STIM_REG_COMMAND;
    block.data_length=1;
    block.data=&command;
    if(!send_short_block(&block))
        printf("Failed to send the command to clear stim config.\n");
}

bool tetra_grip_api::send_short_block(STIM_GUI_MESSAGE_S_BLOCK_T *pblock)
{
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>\nSending: ");
    return STIM_GUI_Send_message(STIMULATOR_ADDRESS1, GUI_ADDRESS, pblock);
}

void tetra_grip_api::read_stim_status_reg(void)
{
    STIM_GUI_MESSAGE_S_BLOCK_T block={};

    block.msg_type=READ_COMMAND;
    block.topic=TOPIC_STIMULATOR;
    block.index=0;
    block.reg_address=STIM_REG_STATUS;
    block.data_length=1;
    block.data=NULL;
    if(!send_short_block(&block))
    {
        printf("Failed to send the read command for the status register.\n");
    }
}

void tetra_grip_api::battery_percentage(void)
{
    STIM_GUI_MESSAGE_S_BLOCK_T block={};

    block.msg_type=READ_COMMAND;
    block.topic=TOPIC_STIMULATOR;
    block.index=0;
    block.reg_address=STIM_REG_BATTERY_CAPACITY_REMAINING;
    block.data_length=1;
    block.data=NULL;
    if(!send_short_block(&block))
    {
        printf("Failed to send the read command for the status register.\n");
    }
}

void tetra_grip_reporter(STIM_GUI_TOPIC_T topic, uint8_t reg, uint32_t value)
{
    emit api.tetraGripEvent(topic, reg, value);

}
