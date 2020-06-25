/* Autores:
 * Samuel Moreno Vincent
 * Santiago Rangel Colón
 * */

#include "encontrarcuadrados.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
encontrarCuadrados::encontrarCuadrados()
{


}
Mat encontrarCuadrados::encontrar(Mat edges, Mat &dst){

    vector<vector<Point> > contours;
    vector<vector<Point> > contoursAux;

    vector<Vec4i> hierarchy;

    // finds contours in "edges" image and stores in contours (hierarchy)
    findContours( edges, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    // iterate through all the top-level contours,draw each connected component with its own random color

    contoursAux = contours;


    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
         Scalar blanco( 255, 255, 255 );
         drawContours( dst, contours, idx, blanco, CV_FILLED, 8, hierarchy );


         double epsilon = arcLength(contours[idx],true)*0.02;
         approxPolyDP(Mat(contours[idx]), contoursAux[idx], epsilon, true);


         int size = contoursAux[idx].size();
         if (size == 4){

             Point a = contoursAux[idx][0];
             Point b = contoursAux[idx][1];
             Point c = contoursAux[idx][2];
             Point d = contoursAux[idx][3];


             float ABC = angulo(a, b, c, 10);
             float ABD = angulo(b, a, d, 10);
             float ACD = angulo(c, d, a, 10);
             float BCD = angulo(b, c, d, 10);


             if ((ABC == 90) && (ABD == 90) && (ACD == 90) && (BCD == 90)){

                if(ladosIguales(a,b,c,d)){

                    Scalar rojo( 255, 0, 0 );
                    drawContours( dst, contoursAux, idx, rojo, CV_FILLED, 8, hierarchy );
                }
             }
        }
    }
    return edges;

}
float encontrarCuadrados::angulo(Point a, Point b, Point c, int _var){

    Point ab;
    Point cb;

    ab.x = b.x - a.x;
    ab.y = b.y - a.y;

    cb.x = b.x - c.x;
    cb.y = b.y - c.y;

    float angba = atan2(ab.y, ab.x);
    float angbc = atan2(cb.y, cb.x);
    float rslt = angba - angbc;
    float rs = (rslt * 180) / 3.141592;

    // Normalizacion:

    int var=_var;

    if (rs < 0){
        rs = -rs;
    }
    if (rs > (90-var) && rs < (90+var)){
        rs = 90;
    }
    if (rs > (270-var) && rs < (270+var)){
        rs = 90;
    }

     return rs;
}

bool encontrarCuadrados::ladosIguales(Point a, Point b, Point c, Point d){

    float distanciaAB = distancia(a, b);
    float distanciaAC = distancia(a, d);
    float distanciaBD = distancia(b, c);
    float distanciaCD = distancia(c, d);

    if(distanciasIguales(distanciaAB,distanciaAC,distanciaBD,distanciaCD, 0.2))return true;
    return false;

}

float encontrarCuadrados::distancia(Point a, Point b){
    float distancia = sqrt((  (b.x-a.x)  *  (b.x-a.x)  )+(  (b.y-a.y)  *  (b.y-a.y)  ));
    return distancia;
}

bool encontrarCuadrados::distanciasIguales(float a, float b, float c, float d, float _var){
    float max = 1+_var;
    float min = 1-_var;

    float ab = a/b;
    float ac = a/c;
    float ad = a/d;
    if(ab > max) return false;
    if(ac > max) return false;
    if(ad > max) return false;
    if(ab < min) return false;
    if(ac < min) return false;
    if(ad < min) return false;
    return true;
}
