#include "mainwindow.h"
#include <QApplication>
#include "point2d.h"
#include "point2d_test.h"
#include "point2d_series.h"
#include "point2d_series_test.h"
#include "matrix.h"
#include "matrix_test.h"
#include "scalar_field.h"
#include "scalar_field_test.h"
#include "vector_field.h"
#include "vector_field_test.h"
int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
    test_gradiend();
}
