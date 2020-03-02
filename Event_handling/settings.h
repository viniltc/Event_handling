#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include "tetra_grip_api.h"
#include "patients.h"
#include <QTimer>
#include <QDebug>
#include <QScreen>
#include <QMessageBox>
#include "qcustomplot.h"

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

 void eventHandler(STIM_GUI_TOPIC_T topic, uint8_t index, uint8_t reg, uint32_t value);
 void sensorEventHandler(uint8_t index, SENSOR_DATA_T *sample);
 void realtimeDataSlot(double x_acceleration_g, double y_acceleration_g, double z_acceleration_g);
 void get_data();

private slots:

 void on_pushButton_open_clicked();

 void on_pushButton_reset_clicked();

private:
    Ui::Settings *ui;
    QTimer dataTimer;
    QCPItemTracer *itemDemoPhaseTracer;
};
#endif // SETTINGS_H
