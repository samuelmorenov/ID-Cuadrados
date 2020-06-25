#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GL/glut.h"


#include <rcdraw.h>

#include "encontrarcuadrados.h"

#include <QScrollBar>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/video/video.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <QCoreApplication>


using namespace cv;
using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer timer; // timer para el slot
    VideoCapture *cap; // objeto para la captura de un frame de video
    RCDraw *visor_source; // visor para la imagen fuente
    RCDraw *visor_target_1; // visor para la imagen procesada 1
    RCDraw *visor_target_2; // visor para la imagen procesada 2
    RCDraw *visor_target_3; // visor para la imagen procesada 3
    QImage *s_img; // Objeto Qimage para la imagen fuente 1
    QImage *t_img_1; // Objeto Qimage para la imagen procesada 1
    QImage *t_img_2; // Objeto Qimage para la imagen procesada 2
    QImage *t_img_3; // Objeto Qimage para la imagen procesada 2

    QScrollBar *scroll_Sigma1;
    QScrollBar *scroll_Sigma2;
    QScrollBar *scroll_UmbralGauss1;
    QScrollBar *scroll_UmbralGauss2;

public slots:
        void compute();
};

#endif // MAINWINDOW_H
