#include "settings.h"
#include "patients.h"
#include "tetra_grip_api.h"
#include "tetra_grip_writer.h"
#include <QApplication>
#include <QDebug>

tetra_grip_api api;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    api.openSerialPort();

    qDebug()<<"main connect"<<QObject::connect(api.serial, SIGNAL(readyRead()), &api, SLOT(readData()));

    Settings w(nullptr);
    w.show();
    return a.exec();
}
