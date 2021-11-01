#ifndef ABELIANPILE_H
#define ABELIANPILE_H

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
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QVector>
#include <vector>
#include <QPoint>
#include <cmath>
#include <math.h>
#include <time.h>
#include <ctime>

using namespace std;


// simulates Abelian Sandpile, where each point can have
// at most 3 grains on it
class AbelianPile
{
public:
  typedef unsigned int uint;

  uint N; // size

  vector < vector <uint> > pile;
  vector <QColor> cols;

  double msToStabilize; // time to run StabilizePile [ms]

  void AddGrain(uint x, uint y, uint numGrains = 1);
  void StabilizePile( );
  void StabilizePileRand(double p = 0.000001);
  void StabilizePileFast( );

  QImage ToQImage( );

  AbelianPile(uint _N = 10);
};

#endif // ABELIANPILE_H




