#pragma once
#include <QMainWindow>
#include "qcustomplot.h"
#include <vector>
#include "lens.h"
#include "laser_device.h"
#include "ior_field.h"
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
private:
    int nx, ny;
    double x_min, x_max, y_min, y_max;
    double dt = 0.01;
    int num_smoothing = 0;
    int number_item = 0;
    std::vector<lens> lenses;
    std::vector<laser_device> lasers;
    ior_field main_field;

    Q_OBJECT
private:
    QCustomPlot *customPlot = nullptr;
    QCPColorMap *colorMap = nullptr;
    QCPColorScale *colorScale = nullptr;
    QStandardItemModel *model = nullptr;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  void drawIOR(QCustomPlot *customPlot);
  void defaultSetting(QCustomPlot *customPlot);

private slots:
  void on_addLensButton_clicked();

  void on_activateButton_clicked();

  void on_addLaserButton_clicked();

  void on_activateButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
