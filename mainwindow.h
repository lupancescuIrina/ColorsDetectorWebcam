#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QMainWindow>
#include <QFileDialog>
#include <QColor>
#include <QColorDialog>
#include <QSlider>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include<QTimer>
#include<iostream>
using namespace std;
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Open_clicked();
    void on_Close_clicked();
    void update_window();
    void gasesteContururiSiDreptunghi(const Mat&poza);
    void trackBars();
    void cautaObiectInPoza(const Mat &poza);

    void contururi(const Mat &poza2);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    VideoCapture cap;
    Mat frame;
    Mat poza,imgHSV;
    QImage qt_image;
    int iLowH, iLowS, iLowV;
    int iHighH, iHighS, iHighV;
    vector<vector<Point> > contours;
    vector <Vec4i> hierarchy;
    Mat  imgTresholded;
    Mat poza2;



};
#endif // MAINWINDOW_H
