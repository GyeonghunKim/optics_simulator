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
  defaultSetting(ui->customPlot);
  // drawIOR(ui->customPlot);
}

lensViewer::~lensViewer()
{
    delete ui;
}
void lensViewer::defaultSetting(QCustomPlot *customPlot){
    QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    this->customPlot = customPlot;
    this->colorMap = colorMap;
    this->colorScale = colorScale;
    this->lens_type = "Spherical_convex";
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
    int nx = ui->N_x->text().toInt();
    int ny = ui->N_y->text().toInt();
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    double x_min = ui->x_min->text().toDouble();
    double x_max = ui->x_max->text().toDouble();
    double y_min = ui->y_min->text().toDouble();
    double y_max = ui->y_max->text().toDouble();

    colorMap->data()->setRange(QCPRange(x_min, x_max), QCPRange(y_min, y_max)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:



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


    std::cout << "setting lens OK" << std::endl;


    // rescale the key (x) and value (y) axes so the whole color map is visible:
    customPlot->rescaleAxes();
}

void lensViewer::on_tryButton_clicked()
{
    std::cout << "removed" << std::endl;
    std::cout << customPlot->removePlottable(colorMap) << std::endl;
    // configure axis rect:
    customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    customPlot->axisRect()->setupFullAxesBox(true);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    int nx = ui->N_x->text().toInt();
    int ny = ui->N_y->text().toInt();
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    double x_min = ui->x_min->text().toDouble();
    double x_max = ui->x_max->text().toDouble();
    double y_min = ui->y_min->text().toDouble();
    double y_max = ui->y_max->text().toDouble();
    colorMap->data()->setRange(QCPRange(x_min, x_max), QCPRange(y_min, y_max)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:

    double loc_x = ui->loc_x->text().toDouble();
    double loc_y = ui->loc_y->text().toDouble();
    double align_x = ui->align_x->text().toDouble();
    double align_y = ui->align_y->text().toDouble();

    double param1 = ui->parameter1->text().toDouble();
    double param2 = ui->parameter2->text().toDouble();
    double lens_rad = ui->radius->text().toDouble();
    double thick = ui->thickness->text().toDouble();

    // setting Lens in optical table
    lens l1(loc_x, loc_y, param1, param2, lens_rad, thick, 1.5, align_x, align_y, this->lens_type);
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


    std::cout << "setting lens OK" << std::endl;


    // rescale the key (x) and value (y) axes so the whole color map is visible:
    customPlot->rescaleAxes();
}

void lensViewer::on_Spherical_convex_clicked()
{
    this->lens_type = "spherical_convex";
}

void lensViewer::on_Spherical_concave_clicked()
{
    this->lens_type = "spherical_concave";
}

void lensViewer::on_Parabolic_convex_clicked()
{
    this->lens_type = "parabolic_convex";
}

void lensViewer::on_Parabolic_concave_clicked()
{
    this->lens_type = "parabolic_concave";
}
