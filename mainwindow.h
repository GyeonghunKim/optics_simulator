#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

  void setupColorMapDemo(QCustomPlot *customPlot);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
