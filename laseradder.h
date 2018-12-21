#pragma once
#include <QDialog>
#include <vector>
#include "laser_device.h"

namespace Ui {
class laserAdder;
}

class laserAdder : public QDialog
{
private:
    std::vector<laser_device> lasers;
    Q_OBJECT

public:
    explicit laserAdder(QWidget *parent = nullptr);
    ~laserAdder();
    std::vector<laser_device> get_lasers();
private slots:
    void on_pushButton_clicked();

private:
    Ui::laserAdder *ui;
};

