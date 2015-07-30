#include <QTcpSocket>
#include <QDebug>
#include <QUrl>

#include "mjpegthread.h"
#include "configfile.h"

void mjpegThread::run()
{
    QTcpSocket *socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    
    QUrl url(cfg->get("src1/url"), QUrl::TolerantMode);

    socket->connectToHost(url.host(), 80);

    if(!socket->waitForConnected(5000))
    {
      qDebug() << "Error: " << socket->errorString();
    }


    while (fRun)
    {
        sleep(1);
    }

    socket->close();
}

void mjpegThread::connected()
{
    qDebug() << "connected...";
    socket->write("GET ");
    socket->write(cfg->get("src1/url").toStdString().c_str());
    socket->write(" HTTP/1.0\r\n\r\n\r\n\r\n");
}

void mjpegThread::disconnected()
{
    qDebug() << "disconnected...";
}

void mjpegThread::readyRead()
{
    array += socket->readAll();

    if(array.contains("\r\n\r\n"))
    {
        int bytes = array.indexOf('\n') + 1;
        QByteArray message = array.left(bytes);
        array = array.mid(bytes);

        //processMessage(message);

        array.clear();
        readyRead();
    }
}
