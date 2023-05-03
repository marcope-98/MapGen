#ifndef EXPORTER_H
#define EXPORTER_H

#include <sstream>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <iomanip>
#include "obstacle.h" // so we inherit also obstaclebase

class Exporter
{
private:
    QString m_filename;
    QDomProcessingInstruction m_xml;
    QDomElement m_sdf;
    QDomElement m_model;
    QDomDocument m_stream;
    int m_obstacles = 0;
public:
    Exporter(QString filename);
    QDomElement addElement(QDomNode &node, const QString& tag, const QString &value= QString());
    // itemtype needed for shape, x,y for position and angle for orientation
    void addEntity(QString uri, QString pose, QString name);
    void addObstacle(ObstacleBase::ItemType type, ObstacleBase::ItemSize size,  float x, float y, float angle);
    void end();
    bool save(QIODevice *file);

};

#endif // EXPORTER_H
