#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include "tetra_grip_api.h"
#include "patients.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Settings; }
QT_END_NAMESPACE

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    Settings(QWidget *parent = nullptr);
    ~Settings();
    Patients *newwindow;

public slots:

 void eventHandler(STIM_GUI_TOPIC_T topic, uint8_t reg, uint32_t value);

private slots:

 void on_pushButton_open_clicked();

private:
    Ui::Settings *ui;
};
#endif // SETTINGS_H
