#include "tomatotimerwindow.h"
#include "ui_tomatotimerwindow.h"
#include <QMessageBox>
#include <QSystemTrayIcon>

#include <QDebug>

TomatoTimerWindow::TomatoTimerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TomatoTimerWindow)
{
    ui->setupUi(this);
    ui->theButton->setText("Tomato It");
    status =  IDLE;
    counter =0;
    timer.stop();
    timer.setInterval(1000);
    sec_counter=0;
    ui->label->setPixmap(QPixmap("://idle.png"));
    trayicon.setIcon(QIcon("://time.png"));
    trayicon.show();
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    connect(&trayicon,SIGNAL(messageClicked()),this,SLOT(topWindow()));
    connect(&trayicon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(onActivate(QSystemTrayIcon::ActivationReason)));
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
}

TomatoTimerWindow::~TomatoTimerWindow()
{
    delete ui;
}

void TomatoTimerWindow::onTimeOut()
{
    //qDebug()<<"Time out."<<endl;
    sec_counter++;

    if(status==WORK)
    {
        int totalsec = 25*60-sec_counter;
        int min = totalsec/60;
        int sec = totalsec%60;
        QString minstr = QString("%1").arg(min);
        QString secstr = QString("%1").arg(sec);

        if(min<10)
        {
            minstr = QString("0")+minstr;
        }

        if(sec<10)
        {
            secstr = QString("0")+secstr;
        }

        ui->theButton->setText("Work "+minstr+":"+secstr);

        if(totalsec<1)
        {
            timer.stop();
            counter++;//a work counted
            toShowSystemNotification("25 min Work ends.\nPlease have a rest!\n");
            onSwitch();
        }
    }
    else if(status == LongRest)
    {
        int totalsec = 10*60-sec_counter;
        int min = totalsec/60;
        int sec = totalsec%60;
        QString minstr = QString("%1").arg(min);
        QString secstr = QString("%1").arg(sec);

        if(min<10)
        {
            minstr = QString("0")+minstr;
        }

        if(sec<10)
        {
            secstr = QString("0")+secstr;
        }

        ui->theButton->setText("Rest "+minstr+":"+secstr);

        if(totalsec<1)
        {
            timer.stop();
            toShowSystemNotification("10 min Rest ends.\nPlease Work for 25 min!\n");
            onSwitch();
        }
    }
    else if(status == ShortRest)
    {
        int totalsec = 5*60-sec_counter;
        int min = totalsec/60;
        int sec = totalsec%60;
        QString minstr = QString("%1").arg(min);
        QString secstr = QString("%1").arg(sec);

        if(min<10)
        {
            minstr = QString("0")+minstr;
        }

        if(sec<10)
        {
            secstr = QString("0")+secstr;
        }

        ui->theButton->setText("Rest "+minstr+":"+secstr);

        if(totalsec<1)
        {
            timer.stop();
            toShowSystemNotification("5 min Rest ends. \nPlease Work for 25 min!");
            onSwitch();
        }
    }
    else
    {
        //
    }
}

void TomatoTimerWindow::onButtonClicked()
{
    //qDebug()<<"The button is clicked!"<<endl;
    sec_counter=0;

    if(status == IDLE)
    {
        //
        sec_counter=0;
        ui->theButton->setText("Work 25:00");
        status=WORK;
        timer.start();
        ui->label->setPixmap(QPixmap("://time.png"));
        trayicon.setIcon(QIcon("://time.png"));
    }
    else if(status == WORK)
    {
        //
        timer.stop();
        ui->theButton->setText("Tomato It");
        status= IDLE;
        ui->label->setPixmap(QPixmap("://idle.png"));
        trayicon.setIcon(QIcon("://time.png"));
    }
    else if(status == ShortRest)
    {
        //
        timer.stop();
        ui->theButton->setText("Tomato It");
        status= IDLE;
        ui->label->setPixmap(QPixmap("://idle.png"));
        trayicon.setIcon(QIcon("://time.png"));
    }
    else if(status == LongRest)
    {
        //
        timer.stop();
        ui->theButton->setText("Tomato It");
        status= IDLE;
        ui->label->setPixmap(QPixmap("://time.png"));
        trayicon.setIcon(QIcon("://time.png"));
    }
    else
    {
        //
        timer.stop();
        ui->theButton->setText("Tomato It");
        status= IDLE;
        ui->label->setPixmap(QPixmap("://time.png"));
        trayicon.setIcon(QIcon("://time.png"));
    }
}

void TomatoTimerWindow::toShowSystemNotification(QString msg)
{
    //QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
    trayicon.showMessage("Tomato Timer",msg,QSystemTrayIcon::Information,10000);
}

void TomatoTimerWindow::onActivate(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        this->activateWindow();

    case QSystemTrayIcon::DoubleClick:
        //this->raise();
        this->activateWindow();
        break;

    case QSystemTrayIcon::MiddleClick:
        this->activateWindow();
        break;

    default:
        ;
    }
}

void TomatoTimerWindow::topWindow()
{
    this->activateWindow();
    this->raise();
}

void TomatoTimerWindow::onSwitch()
{
    this->activateWindow();
    this->raise();
    sec_counter=0;

    if(status == WORK)
    {
        ui->label->setPixmap(QPixmap("://rest.png"));
        trayicon.setIcon(QIcon("://rest.png"));

        if(counter> 2 && (counter-1)%4 == 0)
        {
            status = LongRest;
            counter =0;
            ui->theButton->setText("Rest 05:00");
        }
        else
        {
            status = ShortRest;
            ui->theButton->setText("Rest 10:00");
        }

        timer.start();
    }
    else if(status == LongRest || status == ShortRest)
    {
        ui->label->setPixmap(QPixmap("://time.png"));
        trayicon.setIcon(QIcon("://time.png"));
        status = WORK;
        ui->theButton->setText("Work 25:00");
        timer.start();
    }
    else
    {
        status = IDLE;
        timer.stop();
        ui->theButton->setText("Tomato It");
        ui->label->setPixmap(QPixmap("://idle.png"));
    }
}


