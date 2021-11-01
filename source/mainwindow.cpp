#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->N = 301;
  this->imgSIZE = 601;
  this->stepNr = 0;
  this->pile = new AbelianPile(N);

  ui->imgLabel->setMinimumSize(imgSIZE + 10, imgSIZE + 10);
  ui->imgLabel->setPixmap(QPixmap::fromImage(pile->ToQImage( )).scaled(imgSIZE, imgSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));

  this->isRunning = true;
  on_runButton_clicked( ); // flips [isRunning]

  QTimer::singleShot(100, this, SLOT(Next( )));
} // MainWindow

MainWindow::~MainWindow( ) {
  delete ui;
} // ~MainWindow

void MainWindow::Next( ) {
  if (!isRunning) {
    QTimer::singleShot(40, this, SLOT(Next( )));
    return;
  } // if

  if (stepNr == 0)
    t0 = clock( );

  int nSteps = ui->batchSpinBox->value( );

  //qDebug( ) << "Run AddGrain, nSteps:" << nSteps;

  this->pile->AddGrain(N/2, N/2, nSteps);
  stepNr += nSteps;

  //double stepFreq = double(nSteps) / pile->msToStabilize;

  ui->imgLabel->setPixmap(QPixmap::fromImage(pile->ToQImage( )).scaled(imgSIZE, imgSIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  ui->statusBar->showMessage("Tot #grains = " + QString::number(stepNr/1000)
                             + "k, msToStabalize = " + QString::number(pile->msToStabilize, 'g', 3) + "ms"
                             + ", totSec = " + QString::number(double(double(clock( ) - t0) / CLOCKS_PER_SEC)) + "s.");

//  if (stepNr >= 100*1000) {
//    on_runButton_clicked( ); // makes [isRunning] false
//  } // if

//  uint new_nSteps = (100*stepFreq);
//  new_nSteps = std::max(uint(10 * (new_nSteps / 10)), uint(10));
//  ui->batchSpinBox->setValue(new_nSteps);

  QTimer::singleShot(10, this, SLOT(Next( )));
} // Next

void MainWindow::on_runButton_clicked( ) {
  if (isRunning) {
    ui->runButton->setText("Start");
    isRunning = false;
  } // if
  else {
    ui->runButton->setText("Pause");
    isRunning = true;
  } // else

  ui->runButton->repaint( );
} // on_runButton_clicked
