#ifndef PATIENTS_H
#define PATIENTS_H

#include <QMainWindow>

namespace Ui {
class Patients;
}

class Patients : public QMainWindow
{
    Q_OBJECT

public:
    explicit Patients(QWidget *parent = nullptr);
    ~Patients();

private:
    Ui::Patients *ui;
};

#endif // PATIENTS_H
