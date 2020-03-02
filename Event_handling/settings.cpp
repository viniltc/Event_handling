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
    qDebug()<<"Settings connect"<<connect(&api, &tetra_grip_api::tetraGripSensorEvent,this, &Settings::sensorEventHandler);

    tetra_grip_api::battery_percentage();

    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(2)->setPen(QPen(QColor(110, 255, 40)));

//    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
//    timeTicker->setTimeFormat("%h:%m:%s");
//    customPlot->xAxis->setTicker(timeTicker);
//    customPlot->axisRect()->setupFullAxesBox();
//    customPlot->yAxis->setRange(-1.2, 1.2);

    ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(5);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(-1.5, 1.5);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect( ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),  ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect( ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui-> customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    // connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    // dataTimer.start(0); // Interval 0 means to refresh as fast as possible

    tetra_grip_api::set_sensor_data_rate(SENSOR_ADDRESS_BROADCAST, 100); // sensor data in 100Hz



}

Settings::~Settings()
{
    delete ui;
}

void Settings::eventHandler(STIM_GUI_TOPIC_T topic, uint8_t index, uint8_t reg, uint32_t value)
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

    else if (topic == TOPIC_SENSOR && reg == SENSOR_REG_STREAMING_DATA)
    {
        ui->textBrowser->setText(QString::number(value));
    }


}
void Settings::sensorEventHandler(uint8_t index, SENSOR_DATA_T *sample)
{
    ui->textBrowser->setText("Index = " + QString::number(index) + "\n" +
                "Acceleration, X: " + QString::number(sample->acceleration_g[0]) + "\n" +
                "Acceleration, Y: " + QString::number(sample->acceleration_g[1]) + "\n" +
                "Acceleration, Z: " + QString::number(sample->acceleration_g[2]));

    realtimeDataSlot(sample->acceleration_g[0], sample->acceleration_g[1], sample->acceleration_g[2]);
}

void Settings::on_pushButton_open_clicked()
{
//    this->close();
//    newwindow = new Patients(this);
//    newwindow->show();

}
void Settings::on_pushButton_reset_clicked()
{
    tetra_grip_api::reset_sensors(SENSOR_ADDRESS_BROADCAST);

}

void Settings::realtimeDataSlot(double x_acceleration_g, double y_acceleration_g, double z_acceleration_g)
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.02) // at most add point every 2 ms
    {
      // add data to lines:
    //    ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    //    ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    //    ui->customPlot->graph(2)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.5364));
        ui->customPlot->graph(0)->addData(key, x_acceleration_g);
        ui->customPlot->graph(1)->addData(key, y_acceleration_g);
        ui->customPlot->graph(2)->addData(key, z_acceleration_g);
      // rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->replot();



    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey >2) // average fps over 2 seconds
    {
      ui->statusbar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
}

void Settings::get_data()
{



}



