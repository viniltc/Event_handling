#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Settings; }
QT_END_NAMESPACE

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
};
#endif // SETTINGS_H
