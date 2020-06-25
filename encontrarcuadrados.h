#ifndef ENCONTRARCUADRADOS_H
#define ENCONTRARCUADRADOS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "GL/glut.h"
#include <rcdraw.h>


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/video/video.hpp"

#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "mainwindow.h"
/* Autores:
 * Samuel Moreno Vincent
 * Santiago Rangel Colón
 * */

#include "ui_mainwindow.h"
#include <qdebug.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <QCoreApplication>

using namespace cv;
using namespace std;

class encontrarCuadrados
{
public:
    encontrarCuadrados();
    Mat encontrar(Mat edges, Mat &dst);
    float angulo(Point a, Point b, Point c, int _var);
    bool ladosIguales(Point a, Point b, Point c, Point d);
    float distancia(Point a, Point b);
    bool distanciasIguales(float a, float b, float c, float d, float _var);
};

#endif // ENCONTRARCUADRADOS_H
