#include "patients.h"
#include "ui_patients.h"

Patients::Patients(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Patients)
{
    ui->setupUi(this);
}

Patients::~Patients()
{
    delete ui;
}
