#include "exporter.h"
Exporter::Exporter(QString filename) :  m_filename(filename), m_stream()
{
    m_xml = m_stream.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
    m_stream.appendChild(m_xml);

    m_sdf = m_stream.createElement("sdf");
    m_sdf.setAttribute("version", "1.4");
    m_stream.appendChild(m_sdf);

    m_model = m_stream.createElement("model");
    m_model.setAttribute("name", "mindstorm_map");
    m_sdf.appendChild(m_model);
}



// like add Element but defaults to m_model insteam of node. no need for tag or value given that they are prefixed
void Exporter::addEntity(QString uri, QString pose, QString name)
{
    QDomElement t_include = addElement(m_model, "include");
    addElement(t_include, "uri" , uri);
    addElement(t_include, "pose", pose);
    addElement(t_include, "name", name);
}



QDomElement Exporter::addElement(QDomNode &node, const QString& tag, const QString &value)
{
     QDomElement el = m_stream.createElement(tag);
     node.appendChild(el);
     if(!value.isNull())
     {
         QDomText txt =  m_stream.createTextNode(value);
         el.appendChild(txt);
     }
    return el;
}

void Exporter::addObstacle(ObstacleBase::ItemType type, ObstacleBase::ItemSize size, float x, float y, float angle)
{

    std::stringstream uri;
    std::stringstream name;
    uri << "model://";
    switch (type)
    {
    case ObstacleBase::ITEM_TRIANGLE:
        m_obstacles++;
        uri << "triangle";
        name << "obstacle_" << m_obstacles;
        break;
    case ObstacleBase::ITEM_RECTANGLE:
        m_obstacles++;
        uri << "rectangle";
        name << "obstacle_" << m_obstacles;
        break;
    case ObstacleBase::ITEM_PENTAGON:
        m_obstacles++;
        uri << "pentagon";
        name << "obstacle_" << m_obstacles;
        break;
    case ObstacleBase::ITEM_HEXAGON:
        m_obstacles++;
        uri << "hexagon";
        name << "obstacle_" << m_obstacles;
        break;
    case ObstacleBase::ITEM_GATE:
        uri << "gate";
        name << "gate";
        break;
    case ObstacleBase::ITEM_ROBOT:
        break;
    }


    switch(size)
    {
    case ObstacleBase::SIZE_95:
    uri << "_95";
    break;
    case ObstacleBase::SIZE_142:
    uri << "_142";
    break;
    case ObstacleBase::SIZE_189:
    uri << "_189";
    break;
    case ObstacleBase::SIZE_UNKNOWN:
    break;
    }

    std::stringstream pose;

    pose << std::setprecision(5) << std::fixed << " " << x*0.01/0.62 << " " << y*0.01/0.62 << " 0 0 0 " << angle << " ";


    addEntity(QString::fromStdString(uri.str()), QString::fromStdString(pose.str()),QString::fromStdString(name.str()));
}

void Exporter::end()
{
    addEntity("model://long_black_stripe", " 7.8 0.0 0 0 -0 0 ", "long_stripe_down");
    addEntity("model://long_black_stripe", " 7.8 10.6 0 0 -0 0 ", "long_stripe_up");
    addEntity("model://short_black_stripe", " 0.0 5.3 0 0 0 1.5707963268 ", "short_stripe_left");
    addEntity("model://short_black_stripe", " 15.6 5.3 0 0 0 1.5707963268 ", "short_stripe_right");
    addEntity("model://short_red_stripe", " 2.0 -1.0 0 0 0 0 ", "short_red_stripe");
    addEntity("model://arena_ground", " 7.5 5.0 -0.05 0 -0 0 ", "arena_ground");
}


bool Exporter::save(QIODevice* file)
{
    end();
    QTextStream out(file);
    out << m_stream.toString();
    //m_stream.save(out, IndentSize);
    return true;
}

