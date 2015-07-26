#include "configfile.h"
#include <QXmlStreamReader>
#include <QDebug>

ConfigFile* ConfigFile::instance = NULL;

ConfigFile* ConfigFile::getInstance()
{
    if (!instance)
        instance = new ConfigFile();

    return instance;
}

ConfigFile::~ConfigFile()
{
    delete settings;
}

QString ConfigFile::get(const QString &key)
{
    if(settings->contains(key))
    {
        return settings->value(key).toString();
    }

    return "";
}

bool ConfigFile::LoadConfig(const QString &conf)
{
    qDebug()<<"config: "<<conf;

    QSettings::Format XmlFormat = QSettings::registerFormat("xml", ConfigFile::readXmlFile, ConfigFile::writeXmlFile);

    settings = new QSettings(conf, XmlFormat);

    return isInited = true;
}

bool ConfigFile::readXmlFile(QIODevice &device, QSettings::SettingsMap &map)
{
  QXmlStreamReader xmlReader(&device);
  QStringList elements;

  while (!xmlReader.atEnd() && !xmlReader.hasError())
  {
     xmlReader.readNext();

    if (xmlReader.isStartElement() && xmlReader.name() != "root")
    {
      elements.append(xmlReader.name().toString());
    }
    else if (xmlReader.isEndElement())
    {
      if(!elements.isEmpty()) elements.removeLast();
    }
    else if (xmlReader.isCharacters() && !xmlReader.isWhitespace())
    {
      QString key;

      for(int i = 0; i < elements.size(); i++) {
        if(i != 0) key += "/";
        key += elements.at(i);
      }

      map[key] = xmlReader.text().toString();

    //  qDebug()<<"key: "<<key<<" val: "<<map[key];
    }
  }

  if (xmlReader.hasError())
  {
    qWarning() << xmlReader.errorString();
    return false;
  }

  return true;
}

bool ConfigFile::writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map)
{
  QXmlStreamWriter xmlWriter(&device);

  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("Settings");

  QStringList prev_elements;
  QSettings::SettingsMap::ConstIterator map_i;

  for (map_i = map.begin(); map_i != map.end(); map_i++)
  {

    QStringList elements = map_i.key().split("/");

    int x = 0;
    while(x < prev_elements.size() && elements.at(x) == prev_elements.at(x))
    {
      x++;
    }


    for(int i = prev_elements.size() - 1; i >= x; i--)
    {
      xmlWriter.writeEndElement();
    }

    for (int i = x; i < elements.size(); i++)
    {
      xmlWriter.writeStartElement(elements.at(i));
    }

    xmlWriter.writeCharacters(map_i.value().toString());

    prev_elements = elements;
  }

  for(int i = 0; i < prev_elements.size(); i++)
  {
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  return true;
}
