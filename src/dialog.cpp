#include "include/dialog.h"
#include "ui_dialog.h"



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->saveButton->setToolTip(tr("Export map to sdf file"));

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    m_offset = 0.02*620;
    scene->setSceneRect(m_offset, m_offset, 1.560*620 - 2.*m_offset, 1.060*620 - 2.*m_offset);
    scene->addRect(scene->sceneRect());
    QPen temp(Qt::black);
    //temp.setWidth(8);
    //12.4 + 657.2 -24.8

    QLineF topLine(scene->sceneRect().topLeft() ,scene->sceneRect().topRight());
    QLineF leftLine(scene->sceneRect().topLeft() ,scene->sceneRect().bottomLeft());
    QLineF rightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF bottomLine(scene->sceneRect().bottomLeft(),scene->sceneRect().bottomRight());
    scene->addLine(topLine, temp);
    scene->addLine(leftLine, temp);
    scene->addLine(rightLine, temp);
    scene->addLine(bottomLine, temp);
    new Gate(scene);
}

Dialog::~Dialog()
{
    delete ui;
}

// triangle buttons
void Dialog::on_pushButton_clicked()
{
    new Obstacle(ObstacleBase::SIZE_95,ObstacleBase::ITEM_TRIANGLE,scene);
}

void Dialog::on_pushButton_5_clicked()
{
    new Obstacle(ObstacleBase::SIZE_142,ObstacleBase::ITEM_TRIANGLE,scene);
}

void Dialog::on_pushButton_9_clicked()
{
    new Obstacle(ObstacleBase::SIZE_189,ObstacleBase::ITEM_TRIANGLE,scene);
}

// rectangle buttons
void Dialog::on_pushButton_2_clicked()
{
    new Obstacle(ObstacleBase::SIZE_95,ObstacleBase::ITEM_RECTANGLE,scene);
}

void Dialog::on_pushButton_6_clicked()
{
    new Obstacle(ObstacleBase::SIZE_142,ObstacleBase::ITEM_RECTANGLE,scene);
}

void Dialog::on_pushButton_10_clicked()
{
    new Obstacle(ObstacleBase::SIZE_189,ObstacleBase::ITEM_RECTANGLE,scene);
}

// pentagon buttons
void Dialog::on_pushButton_3_clicked()
{
    new Obstacle(ObstacleBase::SIZE_95,ObstacleBase::ITEM_PENTAGON,scene);
}

void Dialog::on_pushButton_7_clicked()
{
    new Obstacle(ObstacleBase::SIZE_142,ObstacleBase::ITEM_PENTAGON,scene);
}

void Dialog::on_pushButton_11_clicked()
{
    new Obstacle(ObstacleBase::SIZE_95,ObstacleBase::ITEM_PENTAGON,scene);
}

// hexagon buttons
void Dialog::on_pushButton_4_clicked()
{
    new Obstacle(ObstacleBase::SIZE_95,ObstacleBase::ITEM_HEXAGON,scene);
}

void Dialog::on_pushButton_8_clicked()
{
    new Obstacle(ObstacleBase::SIZE_142,ObstacleBase::ITEM_HEXAGON,scene);
}

void Dialog::on_pushButton_12_clicked()
{
    new Obstacle(ObstacleBase::SIZE_189,ObstacleBase::ITEM_HEXAGON,scene);
}

void Dialog::keyReleaseEvent(QKeyEvent * keyEvent)
{
    if(keyEvent->key() == Qt::Key_Backspace || keyEvent->key() == Qt::Key_Delete)
    {
        QList<QGraphicsItem*> selectedItems = scene->selectedItems(); // get list of selected items
        foreach(QGraphicsItem* item, selectedItems)
        {
            if(ObstacleBase* myitem = qgraphicsitem_cast<ObstacleBase *>(item))
            {
                if (myitem->m_Type == ObstacleBase::ITEM_ROBOT)
                    m_robots--;
            }
            scene->removeItem(item);
            delete item;
        }
    }
}



void Dialog::on_saveButton_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Map File"),
                                               QDir::currentPath(),
                                               tr("Structure Data File (*.sdf);;All Files (*)"),0,QFileDialog::DontUseNativeDialog);

          if (fileName.isEmpty())
          {
              return;
          }

          fileName = fileName.contains(".sdf", Qt::CaseSensitive) ? fileName : fileName + ".sdf";
          QFile file(fileName);
          if (!file.open(QFile::WriteOnly | QFile::Text)) {
              QMessageBox::warning(this, tr("SDF"),
                                   tr("Cannot write file %1:\n%2.")
                                   .arg(fileName)
                                   .arg(file.errorString()));
              return;
          }

          Exporter exp(fileName);
          QList<QGraphicsItem*> test = scene->items();
          float tx;
          float ty;
          float tyaw;
          int robot = 0;
          std::stringstream cmd;
          cmd << std::setprecision(3) << std::fixed;
          ObstacleBase::ItemType t_type;
          ObstacleBase::ItemSize t_size;
          for(QGraphicsItem *item : qAsConst(test)){
              if(ObstacleBase* myitem = qgraphicsitem_cast<ObstacleBase *>(item)){
                  switch(myitem->m_Type)
                  {
                    case ObstacleBase::ITEM_TRIANGLE:
                    case ObstacleBase::ITEM_RECTANGLE:
                    case ObstacleBase::ITEM_PENTAGON:
                    case ObstacleBase::ITEM_HEXAGON:
                      tx = myitem->mapToParent(myitem->m_rect.bottomLeft()).x();
                      ty = scene->sceneRect().bottom() - myitem->mapToParent(myitem->m_rect.bottomLeft()).y() + m_offset;
                      tyaw = rangeSymm(atan2(myitem->transform().m11(),myitem->transform().m12()) - M_PI_2);
                      t_type = myitem->m_Type;
                      t_size = myitem->m_Size;
                      exp.addObstacle(t_type, t_size, tx, ty, tyaw);
                      break;
                    case ObstacleBase::ITEM_GATE:
                      tx = myitem->mapToParent(myitem->boundingRect().center()).x();
                      ty = scene->sceneRect().bottom() - myitem->mapToParent(myitem->boundingRect().center()).y() + m_offset;
                      tyaw = myitem->rotation() * M_PI / 180.;
                      t_type = myitem->m_Type;
                      t_size = myitem->m_Size;
                      exp.addObstacle(t_type, t_size, tx, ty, tyaw);
                      break;
                     case ObstacleBase::ITEM_ROBOT:
                      tx = myitem->mapToParent(myitem->m_placeholder).x();
                      ty = scene->sceneRect().bottom() - myitem->mapToParent(myitem->m_placeholder).y() + m_offset;
                      tyaw = rangeSymm(atan2(myitem->transform().m11(),myitem->transform().m12()));
                      cmd << " x_" << robot << ":=" << tx*0.01/0.62
                          << " y_" << robot << ":=" << ty*0.01/0.62
                          << " yaw_" << robot << ":=" << tyaw;
                      robot++;
                      break;
                  }
              }
         }
          std::stringstream prefix;
          prefix << "AR_simulator_gui n:=" << robot << cmd.str();

          exp.save(&file);
            QMessageBox::critical(this,"Terminal input", QString::fromStdString(prefix.str()) );
}


void Dialog::on_pushButton_13_clicked()
{
    if (m_robots <= 2)
    {
        new Robot(scene);
        m_robots++;
    }
}
