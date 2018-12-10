#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

#include "point2d.h"
#include "lens.h"
#include "matrix.h"
#include "scalar_field.h"
#include "vector_field.h"
#include "ior_field.h"
#include "laser.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setGeometry(400, 250, 542, 390);
  drawIOR(ui->customPlot);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawIOR(QCustomPlot *customPlot)
{

  // configure axis rect:
  customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
  customPlot->axisRect()->setupFullAxesBox(true);
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");

  // set up the QCPColorMap:
  QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
  int nx = 5000;
  int ny = 5000;
  colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
  double x_min = -4;
  double x_max = 4;
  double y_min = -4;
  double y_max = 4;
  colorMap->data()->setRange(QCPRange(x_min, x_max), QCPRange(y_min, y_max)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
  // now we assign some data, by accessing the QCPColorMapData instance of the color map:

  lens l1(0, 0, 10, -10, 4, 1.5);
  l1.print_spec();
  ior_field field1(nx, ny, x_min, x_max, y_min, y_max, l1);
  // field1.print();
  auto IOR_matrix = field1.get_data();
  auto IOR = IOR_matrix.get_data();
  for (int xIndex=0; xIndex<nx; ++xIndex)
  {
    for (int yIndex=0; yIndex<ny; ++yIndex)
    {
         colorMap->data()->setCell(xIndex, yIndex, IOR[xIndex][yIndex]);
    }
  }

  point2D<double> loc = {-2, -2};
  point2D<double> dir = {1, 0};
  laser laser1(loc, dir, field1, 0.01);
  laser1.activation();
  // laser1.get_loc().print();
  auto laser_loc = laser1.get_loc();
  auto path_length = laser_loc.get_length();
  // std::cout << path_length << std::endl;
  auto laser_data = laser_loc.get_data();
  QVector<double> x(path_length), y(path_length); // initialize with entries 0..100
  for (int i=0; i<path_length; ++i)
  {
    x[i] = laser_data[i].get_x();
    y[i] = laser_data[i].get_y();
  }
  // create graph and assign data to it:
  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);

  // add a color scale:
  QCPColorScale *colorScale = new QCPColorScale(customPlot);
  customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
  colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
  colorMap->setColorScale(colorScale); // associate the color map with the color scale
  colorScale->axis()->setLabel("Index of Reflectence");

  // set the color gradient of the color map to one of the presets:
  colorMap->setGradient(QCPColorGradient::gpPolar);
  // we could have also created a QCPColorGradient instance and added own colors to
  // the gradient, see the documentation of QCPColorGradient for what's possible.

  // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
  colorMap->rescaleDataRange();

  // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
  QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
  customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
  colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

  // rescale the key (x) and value (y) axes so the whole color map is visible:
  customPlot->rescaleAxes();
}
