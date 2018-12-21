#include "parameteroptimizer.h"
#include "ui_parameteroptimizer.h"

parameterOptimizer::parameterOptimizer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parameterOptimizer)
{
    ui->setupUi(this);
}

parameterOptimizer::~parameterOptimizer()
{
    delete ui;
}
