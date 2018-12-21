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
#include "lensviewer.h"
#include "laseradder.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  defaultSetting(ui->customPlot);
  // drawIOR(ui->customPlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::defaultSetting(QCustomPlot *customPlot){
    QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
    // QCPColorScale *colorScale = new QCPColorScale(customPlot);
    this->customPlot = customPlot;
    this->colorMap = colorMap;

    // this->colorScale = colorScale;

    QStandardItemModel *model = new QStandardItemModel(0, 5, this);
    this->model = model;
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("type 1")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("type 2")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("index")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("loc")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("align")));
    ui->tableView->setModel(model);
}

void MainWindow::on_addLensButton_clicked()
{
    lensViewer lensviewer;
    lensviewer.setModal(true);
    lensviewer.exec();
    auto l = lensviewer.get_lens();
    auto lens_type = lensviewer.get_lens_type();
    lenses.push_back(l);
    // ui->tableWidget->insertRow(1);
    // ui->tableWidget->setItem(lenses.size(), 1, new QTableWidgetItem(QString::fromStdString(lens_type)));
    // ui->tableWidget->update();
    // ui->tableWidget->isSortingEnabled()
    QStandardItem *item = new QStandardItem(QString::fromStdString(lens_type));
    model->setItem(number_item, 0, new QStandardItem(QString("Lens")));
    model->setItem(number_item, 1, item);
    model->setItem(number_item, 2, new QStandardItem(QString::number(lenses.size())));
    model->setItem(number_item, 3, new QStandardItem(QString::fromStdString(l.get_loc_str())));
    model->setItem(number_item, 4, new QStandardItem(QString::fromStdString(l.get_align_str())));
    number_item++;
}

void MainWindow::on_activateButton_clicked()
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
    // QCPColorScale *colorScale = new QCPColorScale(customPlot);

    int nx = ui->N_x->text().toInt();
    int ny = ui->N_y->text().toInt();
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    double x_min = ui->x_min->text().toDouble();
    double x_max = ui->x_max->text().toDouble();
    double y_min = ui->y_min->text().toDouble();
    double y_max = ui->y_max->text().toDouble();
    this->dt = ui->dt->text().toDouble();
    this->num_smoothing = ui->number_smooting->text().toInt();

    colorMap->data()->setRange(QCPRange(x_min, x_max), QCPRange(y_min, y_max)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    ior_field tmp_field(nx, ny, x_min, x_max, y_min, y_max, lenses[0]);
    for(auto i = 1; i < lenses.size(); ++i){
        ior_field ttmp_field(nx, ny, x_min, x_max, y_min, y_max, lenses[i]);
        tmp_field = tmp_field + ttmp_field;
    }

    main_field = tmp_field;

    auto IOR_matrix = main_field.get_data();
    auto IOR = IOR_matrix.get_data();

    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
           colorMap->data()->setCell(xIndex, yIndex, IOR[xIndex][yIndex]);
      }
    }

    QCPColorScale *colorScale = new QCPColorScale(customPlot);
    customPlot->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorMap->setColorScale(colorScale);
    colorScale->axis()->setLabel("Index of Reflectence");
    colorMap->setGradient(QCPColorGradient::gpPolar);
    colorMap->rescaleDataRange();
    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
    customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    customPlot->rescaleAxes();
    customPlot->update();
}

void MainWindow::on_addLaserButton_clicked()
{
    laserAdder laseradder;
    laseradder.setModal(true);
    laseradder.exec();

    auto las = laseradder.get_lasers();
    for(auto i = 0; i < las.size(); ++i){
        lasers.push_back(las[i]);
        model->setItem(number_item, 0, new QStandardItem(QString("Laser")));
        model->setItem(number_item, 1, new QStandardItem(QString("Laser")));
        model->setItem(number_item, 2, new QStandardItem(QString::number(lasers.size())));
        model->setItem(number_item, 3, new QStandardItem(QString::fromStdString(las[i].get_loc_str())));
        model->setItem(number_item, 4, new QStandardItem(QString::fromStdString(las[i].get_align_str())));
        number_item++;
    }
}

void MainWindow::on_activateButton_2_clicked()
{
    for(int i = 0; i < lasers.size(); ++i){
    // setting laser1 in optical table
    this->num_smoothing = ui->number_smooting->text().toInt();
    point2D<double> loc = lasers[i].get_loc();
    point2D<double> dir = lasers[i].get_dir();
    laser laser(loc, dir, main_field, dt);
    laser.activation(num_smoothing);
    auto laser_loc = laser.get_loc();
    auto path_length = laser_loc.get_length();
    // std::cout << path_length << std::endl;
    auto laser_data = laser_loc.get_data();
    QVector<double> x1(path_length), y1(path_length); // initialize with entries 0..100
    for (int i=0; i<path_length; ++i)
    {
      x1[i] = laser_data[i].get_x();
      y1[i] = laser_data[i].get_y();
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(i)->setData(x1, y1);
    customPlot->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 7));
  }
    customPlot->update();
    std::cout << "draw on finished" << std::endl;



}

