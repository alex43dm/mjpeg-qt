#ifndef MJPEGTHREAD_H
#define MJPEGTHREAD_H

#include <QThread>

class mjpegThread : public QThread
{
    Q_OBJECT
public:
    void Stop(){fRun = false;};

private:
    bool fRun;
    void run();
};

#endif // MJPEGTHREAD_H
