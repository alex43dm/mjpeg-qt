#include <QDebug>

#include "mjpegthread.h"

void mjpegThread::run()
{
    qDebug()<<"From worker thread: "<<currentThreadId();
    //    QString s = cfg->get("src1/sizeX");

    while (fRun)
    {
        sleep(1);
    }
}
