#include "tomatotimerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TomatoTimerWindow w;
    w.show();

    return a.exec();
}
