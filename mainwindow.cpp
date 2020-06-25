/*La implementación de la clase Mainwindow:
 *

   ->Constructor:
   Dibujo de la ventana principal
   Iniciar la cámara
   Crear el objeto imagen fuente  (s_img)
   Crear el objeto visor de la imagen fuente 1 (visor_source)
    Arrancar el connect para el compute
   ->Destructor:

   ->compute (en SLOT) :
   Declarar las matrices imagen Mat:
          captured_image, edges y dst;
   Capturar un frame de una cámara
   Copiar el frame al visor fuente

   Procesar la imagen de la cámara:
            // Captures a frame....
            // Paso a gris
            // binarizes (GaussianBlur and Canny)
            // finds contours (connected components)
            // show contours in randomize color

   Copiar la imagen procesada al visor target 1
   Copiar la imagen procesada al visor target 2
   Copiar la imagen procesada al visor target 3
   Actualizar los cuatro visores.

*/

/* Autores:
 * Samuel Moreno Vincent
 * Santiago Rangel Colón
 * */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <math.h>
#include <cmath>



// Constructor member
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cap = new VideoCapture(0); // init object camera 1

    cap->set(CV_CAP_PROP_FRAME_WIDTH,320); // fix width
    cap->set(CV_CAP_PROP_FRAME_HEIGHT,240); // fix heigth


    s_img = new QImage(320,240, QImage::Format_RGB888);

    t_img_1 = new QImage(320,240, QImage::Format_Indexed8);
    t_img_2 = new QImage(320,240, QImage::Format_RGB888);
    t_img_3 = new QImage(320,240, QImage::Format_Indexed8);

    visor_source = new RCDraw(320,240, s_img, ui->SourceFrame);
    visor_target_1 = new RCDraw(320,240, t_img_1, ui->TargetFrame_1);
    visor_target_2 = new RCDraw(320,240, t_img_2, ui->TargetFrame_2);
    visor_target_3 = new RCDraw(320,240, t_img_3, ui->TargetFrame_3);

    scroll_Sigma1 = ui->ScrollBarSigmaGaussiana;
    scroll_Sigma2 = ui->ScrollBarSigmaGaussiana_2;
    scroll_UmbralGauss1 = ui->ScrollBarUmbralCanny;
    scroll_UmbralGauss2 = ui->ScrollBarUmbralCanny_2;


    connect(&timer,SIGNAL(timeout()),this,SLOT(compute()));
    timer.start(160);
}

// Destructor member
MainWindow::~MainWindow()
{
    delete ui;
    delete cap;
    delete s_img;
    delete t_img_1;
    delete t_img_2;
    delete t_img_3;
    delete visor_source;
    delete visor_target_1;
    delete visor_target_2;
    delete visor_target_3;
    delete scroll_Sigma1;
    delete scroll_Sigma2;
    delete scroll_UmbralGauss1;
    delete scroll_UmbralGauss2;
 }
// implementación del bucle de proceso en SLOT
void MainWindow::compute()
{
   Mat captured_image, edges;

   ////////////////// CAMERA  //////////////////////////
   if(!cap->isOpened())  // check if we succeeded
       exit(-1);
   // get a new frame from camera 1
   *cap >> captured_image;

   // BGR to RGB
   cvtColor(captured_image, captured_image, CV_BGR2RGB,1);
   //copy captured_image_1 to s_img_1 (visor_source_1)
   memcpy(s_img->bits(),captured_image.data,
          captured_image.rows*captured_image.cols*sizeof(uchar)*3 );
   visor_source->update();

   // RGB2GRAY
   cvtColor(captured_image, edges, CV_RGB2GRAY,1);
   // Gaussian Blur
   float sigma1 = scroll_Sigma1->value();
   float sigma2 = scroll_Sigma2->value();
   GaussianBlur(edges, edges,Size(7,7),sigma1, sigma2);
   memcpy(t_img_3->bits(),edges.data,
          edges.rows*edges.cols*sizeof(uchar) );
   visor_target_3->update();

   // Canny filter (binary)
   float umbral1 = scroll_UmbralGauss1->value();
   float umbral2 = scroll_UmbralGauss2->value();

   Canny(edges, edges, umbral1, umbral2, 3);
   Mat dst = Mat::zeros(edges.rows, edges.cols, CV_8UC3); // fill dst to zeros
   edges = edges > 1;
   //copy edges to t_img_1 (visor_target_1)
   memcpy(t_img_1->bits(),edges.data,
          edges.rows*edges.cols*sizeof(uchar) );
   visor_target_1->update();

   ///////////////////////////////
   ///                         ///
   ///                         ///
   /// Find and draw contours  ///
   ///                         ///
   ///                         ///
   ///////////////////////////////

   encontrarCuadrados e;
   edges=e.encontrar(edges, dst);

   //copy dst to t_img_1 (visor_target_2)
   memcpy(t_img_2->bits(),dst.data,dst.rows*dst.cols*sizeof(uchar)*3 );
   visor_target_2->update();

}

