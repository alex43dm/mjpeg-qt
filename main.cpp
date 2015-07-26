#include <QApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>

#include <QDebug>

//#include "config.h"
#include "configfile.h"
#include "mjpegthread.h"

#define VERSION "0.0.1"

ConfigFile *cfg;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName(argv[0]);
    QCoreApplication::setApplicationVersion(VERSION);

    QCommandLineParser parser;

    QCommandLineOption debugOption("d",
               QCoreApplication::translate("main", "Debug mode"),
               "debug","false");
    parser.addOption(debugOption);

    QCommandLineOption configFileOption("c",
               QCoreApplication::translate("main","The config file."),
               "config",
               "config.xml");
    parser.addOption(configFileOption);

    parser.process(app);

    cfg = ConfigFile::getInstance();
    cfg->LoadConfig(parser.value(configFileOption));

    cfg->debug = parser.isSet(debugOption);

    mjpegThread mth;
    mth.start();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
