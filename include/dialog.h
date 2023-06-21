#ifndef DIALOG_H
#define DIALOG_H

#include "exporter.h"
#include "gate.h"
#include "misc.h"
#include "obstacle.h"
#include "robot.h"
#include <QDialog>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <vector>

namespace Ui
{
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_10_clicked();
  void on_pushButton_11_clicked();
  void on_pushButton_12_clicked();
  void keyReleaseEvent(QKeyEvent *event);

  void on_saveButton_clicked();

  void on_pushButton_13_clicked();

private:
  Ui::Dialog *    ui;
  QGraphicsScene *scene;
  int             m_robots = 0;
  qreal           m_offset;

  std::vector<Robot *> robots;
};

#endif // DIALOG_H
