#pragma once
#include "qcustomplot.h"
#include <QDialog>

namespace Ui {
class lensViewer;
}

class lensViewer : public QDialog
{
private:
    int nx, ny;
    double x_min, x_max, y_min, y_max;

    Q_OBJECT
public:
    explicit lensViewer(QWidget *parent = nullptr);
    ~lensViewer();
  void drawIOR(QCustomPlot *customPlot);
private slots:
  void on_tryButton_clicked();

private:
    Ui::lensViewer *ui;
};
