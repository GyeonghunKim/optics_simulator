#pragma once
#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  void drawIOR(QCustomPlot *customPlot);
private:
    Ui::MainWindow *ui;
};
