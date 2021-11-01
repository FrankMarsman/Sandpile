#include "abelianpile.h"


// adds one grain to pile[x][y] and then
// stabalizes the pile
void AbelianPile::AddGrain(uint x, uint y, uint numGrains) {
  if (x >= N || y >= N) {
    qDebug( ) << "Error in AddGrain! x y =" << x << y;
    return;
  } // if

  pile[x][y] += numGrains;
  //StabilizePileRand( );
  StabilizePile( );
} // AddGrain


// functions topples all unstable points until none are left
// and we thus reached a stable configuration
void AbelianPile::StabilizePile( ) {
  time_t t0 = clock( );
  bool isStable;
  uint counter = 0;
  uint fac;
  do {
    isStable = true;
    counter++;
    // topple unstable points:
    for (uint i = 1; i < N - 1; i++) {
      for (uint j = 1; j < N - 1; j++) {
        if (pile[i][j] > 3) {
          isStable = false;
          fac = pile[i][j] / 4;
          pile[i][j] -= 4 * fac;
          // add to neighbors:
          pile[i-1][j]+= fac;
          pile[i+1][j]+= fac;
          pile[i][j-1]+= fac;
          pile[i][j+1]+= fac;
        } // if
      } // for
    } // for
    // empty border points:
    for (uint i = 0; i < N; i++) {
      pile[i][0] = 0;
      pile[0][i] = 0;
      pile[i][N-1] = 0;
      pile[N-1][i] = 0;
    } // for

//    // empty TEMP border points:
//    for (uint i = N*0.15; i < N*0.18; i++)
//      for (uint j = N*0.45; j < N*0.55; j++) {
//        pile[N/2 + i][j] = 0;
//        pile[N/2 - i][j] = 0;
//      } // for
  } // do
  while (isStable == false);

  this->msToStabilize = 1000 * double(double(clock( ) - t0) / CLOCKS_PER_SEC);
  //qDebug( ) << "StabilizePile done in" << counter << "steps";
} // StabilizePile


// functions topples all unstable points until none are left
// and we thus reached a stable configuration
void AbelianPile::StabilizePileRand(double p) {
  time_t t0 = clock( );
  bool isStable;
  uint counter = 0;
  vector <uint> temp;
  uint num1, num2;
  do {
    isStable = true;
    counter++;
    // topple unstable points:
    for (uint i = 1; i < N - 1; i++) {
      for (uint j = 1; j < N - 1; j++) {
        if (pile[i][j] > 3) {
          isStable = false;
          pile[i][j] -= 4;

          // add to neighbors:
          temp = vector <uint> (4, 1);
          bool swap = ((double(rand( )) / RAND_MAX) < p)? true : false;

          if (swap) {
            num1 = rand( ) % 4;
            num2 = rand( ) % 4;

            while (num1 == num2)
              num2 = rand( ) % 4;

            temp[num1]--;
            temp[num2]++;
          } // if

          pile[i-1][j] += temp[0];
          pile[i+1][j] += temp[1];
          pile[i][j-1] += temp[2];
          pile[i][j+1] += temp[3];
        } // if
      } // for
    } // for
    // empty border points:
    for (uint i = 0; i < N; i++) {
      pile[i][0] = 0;
      pile[0][i] = 0;
      pile[i][N-1] = 0;
      pile[N-1][i] = 0;
    } // for
  } // do
  while (isStable == false);

  this->msToStabilize = 1000 * double(double(clock( ) - t0) / CLOCKS_PER_SEC);
  //qDebug( ) << "StabilizePile done in" << counter << "steps";
} // StabilizePileRand


// functions topples all unstable points until none are left
// and we thus reached a stable configuration
void AbelianPile::StabilizePileFast( ) {
  time_t t0 = clock( );
  bool isStable;
  uint counter = 0;
  uint fac;

  vector < pair <uint, uint> > nonStables, tempNonStables;
  vector < vector <bool> > defaultStablePoints(N, vector <bool> (N, true));
  // empty border points:
  for (uint i = 0; i < N; i++) {
    defaultStablePoints[i][0] = false;
    defaultStablePoints[0][i] = false;
    defaultStablePoints[i][N-1] = false;
    defaultStablePoints[N-1][i] = false;
  } // for

  vector < vector <bool> > stablePoints = defaultStablePoints;

  for (uint i = 1; i < N - 1; i++) {
    for (uint j = 1; j < N - 1; j++) {
      if (pile[i][j] > 3) {
        stablePoints[i][j] = false;
        nonStables.push_back(pair <uint, uint> (i, j));
      } // if
    } // for
  } // for

  uint x, y;
  while (nonStables.size( ) > 0) {
    isStable = true;
    counter++;
    tempNonStables.clear( );
    stablePoints = defaultStablePoints;

    for (uint k = 0; k < nonStables.size( ); k++) {
      x = nonStables[k].first;
      y = nonStables[k].second;
      if (pile[x][y] > 3) {
        isStable = false;
        fac = pile[x][y] / 4;
        pile[x][y] -= 4 * fac;
        // add to neighbors:
        pile[x-1][y]+= fac;
        pile[x+1][y]+= fac;
        pile[x][y-1]+= fac;
        pile[x][y+1]+= fac;

        if (stablePoints[x-1][y] && pile[x-1][y] > 3) {
          stablePoints[x-1][y] = false;
          tempNonStables.push_back(pair <uint, uint> (x-1, y));
        } // if
        if (stablePoints[x+1][y] && pile[x+1][y] > 3) {
          stablePoints[x+1][y] = false;
          tempNonStables.push_back(pair <uint, uint> (x+1, y));
        } // if
        if (stablePoints[x][y-1] && pile[x][y-1] > 3) {
          stablePoints[x][y-1] = false;
          tempNonStables.push_back(pair <uint, uint> (x, y-1));
        } // if
        if (stablePoints[x][y+1] && pile[x][y+1] > 3) {
          stablePoints[x][y+1] = false;
          tempNonStables.push_back(pair <uint, uint> (x, y+1));
        } // if
      } // if
    } // for

    // empty border points:
    for (uint i = 0; i < N; i++) {
      pile[i][0] = 0;
      pile[0][i] = 0;
      pile[i][N-1] = 0;
      pile[N-1][i] = 0;
    } // for

    nonStables.clear( );
    nonStables = tempNonStables;
  } // while

  this->msToStabilize = 1000 * double(double(clock( ) - t0) / CLOCKS_PER_SEC);
  qDebug( ) << "StabilizePileFast done in" << counter << "steps";
} // StabilizePileFast

QImage AbelianPile::ToQImage( ) {
  QImage img(QSize(N, N), QImage::Format_ARGB32);
  for (uint i = 0; i < N; i++) {
    for (uint j = 0; j < N; j++) {
      img.setPixelColor(i, j, cols[pile[i][j]]);
    } // for
  } // for
  return img;
} // ToQImage

AbelianPile::AbelianPile(uint _N) {
  this->N = _N;

  for (uint i = 0; i < N; i++) {
    vector <uint> row(N, 1);

    for (uint k = 0; k < N; k++)
      //row[k] = (k + i) % 2;
      //row[k] = (k/20 + i/20) % 2;
      row[k] = 0;

    this->pile.push_back(row);
  } // for

  this->cols.push_back(QColor(255, 255, 255)); // [0]
  this->cols.push_back(QColor(255, 0, 0)); // [1]
  this->cols.push_back(QColor(0, 255, 0)); // [2]
  this->cols.push_back(QColor(0, 0, 255)); // [3]
} // AbelianPile
