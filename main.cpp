/* Tarea 1.
Gestión de la ventana principal de un proyecto QT
  de Imagen Digital que utiliza una cámara, un visor
  para la imagen capturada y dos visores para las
  imágenes procesadas con las siguientes operaciones :
            // Captures a frame....
            // binarizes (GaussianBlur and Canny)
            // finds contours (connected components)
            // show contours in randomize color
            // P. Moreno. Cáceres. 2013.
*/

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication guau(argc, argv);
    MainWindow w;
    w.show();
    return guau.exec();
}
