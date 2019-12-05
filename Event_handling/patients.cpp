#include "patients.h"
#include "ui_patients.h"

Patients::Patients(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Patients)
{
    ui->setupUi(this);
     connect(&api, &tetra_grip_api::tetraGripEvent,this, &Patients::eventHandlerTwo);
}

Patients::~Patients()
{
    delete ui;
}

void Patients::eventHandlerTwo(STIM_GUI_TOPIC_T topic, uint8_t reg, uint32_t value)
{

   ui->label_patients->setText("Patients slot called");

}
