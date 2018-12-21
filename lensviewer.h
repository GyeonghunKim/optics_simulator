#pragma once
#include "qcustomplot.h"
#include "lens.h"
#include <QDialog>

namespace Ui {
class lensViewer;
}

class lensViewer : public QDialog
{
private:
    int nx, ny;
    double x_min, x_max, y_min, y_max;
    std::string lens_type;
    lens l;
    Q_OBJECT
private:
    QCustomPlot *customPlot = nullptr;
    QCPColorMap *colorMap = nullptr;
    QCPColorScale *colorScale = nullptr;

public:
    explicit lensViewer(QWidget *parent = nullptr);
    ~lensViewer();
  void defaultSetting(QCustomPlot *customPlot);
  lens get_lens();
  std::string get_lens_type();
private slots:
  void on_tryButton_clicked();

  void on_Spherical_convex_clicked();

  void on_Spherical_concave_clicked();

  void on_custom_button_clicked();

  void on_Parabolic_convex_clicked();

  void on_applyButton_clicked();



private:
    Ui::lensViewer *ui;
};
