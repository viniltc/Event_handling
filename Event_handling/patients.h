#ifndef PATIENTS_H
#define PATIENTS_H

#include <QMainWindow>
#include "tetra_grip_api.h"

namespace Ui {
class Patients;
}

class Patients : public QMainWindow
{
    Q_OBJECT

public:
    explicit Patients(QWidget *parent = nullptr);
    ~Patients();

public slots:

 void eventHandlerTwo(STIM_GUI_TOPIC_T topic, uint8_t reg, uint32_t value);

private:
    Ui::Patients *ui;
};

#endif // PATIENTS_H
