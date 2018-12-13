#include "lensviewer.h"
#include "ui_lensviewer.h"

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

lensViewer::lensViewer(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::lensViewer)
{
  ui->setupUi(this);
  // setGeometry(400, 250, 542, 390);
  drawIOR(ui->customPlot);
}

lensViewer::~lensViewer()
{
    delete ui;
}

void lensViewer::drawIOR(QCustomPlot *customPlot)
{
  // configure axis rect:
  customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
  customPlot->axisRect()->setupFullAxesBox(true);
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");

  // set up the QCPColorMap:
  QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
  this->nx = 3000;
  this->ny = 3000;
  colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
  this->x_min = -8;
  this->x_max = 8;
  this->y_min = -8;
  this->y_max = 8;
  colorMap->data()->setRange(QCPRange(x_min, x_max), QCPRange(y_min, y_max)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
  // now we assign some data, by accessing the QCPColorMapData instance of the color map:
}

void lensViewer::on_tryButton_clicked()
{
    QCustomPlot *customPlot = ui->customPlot;
    // setting Lens in optical table
    lens l1(0, 0, 2.25, 2.25, 3, 1.5, "parabolic_convex");
    l1.print_spec();
    ior_field field1(nx, ny, x_min, x_max, y_min, y_max, l1);

    // lens l2(4, 0, 10, -10, 6, 1.5, "spherical_convex");
    // l2.print_spec();
    // ior_field field2(nx, ny, x_min, x_max, y_min, y_max, l2);
    // ior_field field0 = field1 + field2;
    ior_field field0 = field1;
    // field1.print();
    auto IOR_matrix = field0.get_data();
    auto IOR = IOR_matrix.get_data();
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
           colorMap->data()->setCell(xIndex, yIndex, IOR[xIndex][yIndex]);
      }
    }

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
