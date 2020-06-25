#-------------------------------------------------
#
# Project created by QtCreator 2013-02-27T12:38:09
#
#-------------------------------------------------

QT       += core gui opengl xml 

TARGET = proyID_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
rcdraw.cpp\
    encontrarcuadrados.cpp

HEADERS  += mainwindow.h\
               rcdraw.h \
    encontrarcuadrados.h

LIBS += -L/usr/local/lib  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching -lopencv_videoio -lopencv_imgcodecs -lglut

INCLUDEPATH += -I/usr/local/include

FORMS    += mainwindow.ui
