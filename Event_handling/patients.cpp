#include "patients.h"
#include "ui_patients.h"
#include<QDebug>

Patients::Patients(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Patients)
{
    ui->setupUi(this);
    qDebug()<<"Patients connect"<<connect(&api, &tetra_grip_api::tetraGripEvent,this, &Patients::eventHandlerTwo);


    tetra_grip_api::battery_percentage();
}

Patients::~Patients()
{
    delete ui;
}

void Patients::eventHandlerTwo(STIM_GUI_TOPIC_T topic, uint8_t reg, uint32_t value)
{

   ui->label_patients->setText("Patients slot called");

}
