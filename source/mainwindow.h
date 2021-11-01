#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QCoreApplication>
#include <QTextStream>
#include <QImage>
#include <QPainter>
#include <QFont>
#include <QColor>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <time.h>
#include <ctime>
#include <cmath>
#include <math.h>
#include <vector>
#include <algorithm>

#include "abelianpile.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  int N; // size of pile grid
  int imgSIZE; // size of image
  int stepNr; // how many sim steps

  time_t t0;

  bool isRunning;
  AbelianPile * pile;

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow( );


public slots:
  void Next( );

private slots:
  void on_runButton_clicked( );

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
