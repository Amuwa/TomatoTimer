#ifndef TOMATOTIMERWINDOW_H
#define TOMATOTIMERWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QSystemTrayIcon>

namespace Ui {
class TomatoTimerWindow;
}

class TomatoTimerWindow : public QDialog
{
    Q_OBJECT

    int counter ;
    int sec_counter;
public:
    explicit TomatoTimerWindow(QWidget *parent = 0);
    ~TomatoTimerWindow();
    enum Status{
        IDLE,
        WORK,
        ShortRest,
        LongRest
    } status;
public slots:
    void onButtonClicked();
    void onTimeOut();
    void toShowSystemNotification(QString msg);
    void onActivate(QSystemTrayIcon::ActivationReason r);
    void onSwitch();
    void topWindow();


private:
    Ui::TomatoTimerWindow *ui;
    QTimer timer;
    QSystemTrayIcon trayicon;
};

#endif // TOMATOTIMERWINDOW_H
