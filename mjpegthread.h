#ifndef MJPEGTHREAD_H
#define MJPEGTHREAD_H

#include <QTcpSocket>
#include <QThread>

class mjpegThread : public QThread
{
    Q_OBJECT
public:
    void Stop(){fRun = false;};

signals:
    
public slots:
    void connected();
    void disconnected();
    void readyRead();

private:
    QTcpSocket *socket;
    QByteArray array;
    bool fRun;
    void run();
};

#endif // MJPEGTHREAD_H
