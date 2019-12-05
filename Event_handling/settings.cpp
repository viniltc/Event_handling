#include "settings.h"
#include "ui_settings.h"
#include <QtSerialPort/QSerialPort>
#include "tetra_grip_api.h"
#include <QDebug>


Settings::Settings(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    qDebug()<<"Settings connect"<<connect(&api, &tetra_grip_api::tetraGripEvent,this, &Settings::eventHandler);

    tetra_grip_api::battery_percentage();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::eventHandler(STIM_GUI_TOPIC_T topic, uint8_t reg, uint32_t value)
{


    if (topic==TOPIC_STIMULATOR)
    {
        switch(reg)
        {
        case STIM_REG_BATTERY_CAPACITY_REMAINING:

             ui->label_settings->setText("Battery remaining: "+QString::number(value)+"%");
        break;
        }
    }


}

void Settings::on_pushButton_open_clicked()
{
    this->close();
    newwindow = new Patients(this);
    newwindow->show();
}
