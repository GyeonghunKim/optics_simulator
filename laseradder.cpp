#include "laseradder.h"
#include "ui_laseradder.h"
#include "laser_device.h"


laserAdder::laserAdder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::laserAdder)
{
    ui->setupUi(this);
}

laserAdder::~laserAdder()
{
    delete ui;
}

void laserAdder::on_pushButton_clicked()
{
    if(ui->singleRadioButton->isChecked()){
        laser_device l(ui->singleLoc_x->text().toDouble(),
                       ui->singleLoc_y->text().toDouble(),
                       ui->singleDir_x->text().toDouble(),
                       ui->singleDir_y->text().toDouble());
        lasers.push_back(l);
    }
    else{
        int N_laser = ui->numberLaser->text().toInt();
        double x_start = ui->multiLocFrom_x->text().toDouble();
        double y_start = ui->multiLocFrom_y->text().toDouble();
        double x_end = ui->multiLocTo_x->text().toDouble();
        double y_end = ui->multiLocTo_y->text().toDouble();
        double dir_x_start = ui->multiDirFrom_x->text().toDouble();
        double dir_y_start = ui->multiDirFrom_y->text().toDouble();
        double dir_x_end = ui->multiDirTo_x->text().toDouble();
        double dir_y_end = ui->multiDirTo_y->text().toDouble();
        double dx = (x_end - x_start) / (N_laser - 1);
        double dy = (y_end - y_start) / (N_laser - 1);
        double ddirx = (dir_x_end - dir_x_start) / (N_laser - 1);
        double ddiry = (dir_y_end - dir_y_start) / (N_laser - 1);
        for(auto i = 0; i < N_laser; ++i){
            laser_device l(x_start + dx * i,
                           y_start + dy * i,
                           dir_x_start + ddirx * i,
                           dir_y_start + ddiry * i);
            lasers.push_back(l);
        }
    }
    this->close();
}

std::vector<laser_device> laserAdder::get_lasers()
{
    return lasers;
}
