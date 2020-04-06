#include "mainwindow.h"
#include "ui_mainwindow.h"

RNG rng(1234);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer= new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Open_clicked()
{
    cap.open(0);
    if(!cap.isOpened())
    {
       cout<<"camera is not open"<<endl;

    }
    else
    {
        connect(timer,SIGNAL(timeout()), this, SLOT(update_window()));
        timer->start(20);
    }
}

void MainWindow::on_Close_clicked()
{
    disconnect(timer, SIGNAL(timeout()),this, SLOT(update_window()));
    cap.release();
    Mat image= Mat::zeros(frame.size(),CV_8UC3);
    qt_image=QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
    ui->Label->setPixmap(QPixmap::fromImage(qt_image));
    ui->Label->resize(ui->Label->pixmap()->size());
    cout<<"camera is closed";
}

void MainWindow::update_window()
{
    cap>>frame;
    cvtColor(frame, frame, CV_RGB2BGR);
    qt_image=QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888);
    ui->Label->setPixmap(QPixmap::fromImage(qt_image));
    ui->Label->resize(ui->Label->pixmap()->size());
    frame.copyTo(poza);
     trackBars();
     cautaObiectInPoza(poza);


}
void MainWindow::trackBars()
{
    namedWindow("Control",CV_WINDOW_AUTOSIZE);
    createTrackbar("LowH","Control",&iLowH,179);
    createTrackbar("HighH","Control",&iHighH,179);
    createTrackbar("LowS","Control",&iLowS,255);
    createTrackbar("HighS","Control",&iHighS,255);
    createTrackbar("LowV","Control",&iLowV,255);
    createTrackbar("HighV","Control",&iHighV,255);
    cout<<"iLowH="<<iLowH<<endl;
}
void MainWindow:: cautaObiectInPoza(const Mat &poza)
{

    while(true)
    {

        cvtColor(poza,imgHSV,COLOR_BGR2HSV);
        inRange(imgHSV,Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV),imgTresholded);
        erode(imgTresholded,imgTresholded,getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        dilate(imgTresholded,imgTresholded,getStructuringElement(MORPH_ELLIPSE, Size(5,5)));

        //aplicam inchidere pentru a elimina obiectele mici din prim plan
         dilate(imgTresholded,imgTresholded,getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
         erode(imgTresholded,imgTresholded,getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        namedWindow("Cauta obiect",CV_WINDOW_AUTOSIZE);
        imshow("Cauta obiect",imgTresholded);
        if(waitKey(30)>0)
        {
            break;
        }
    }

}
void MainWindow::contururi(const Mat &poza2)
{
    findContours(poza2,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE,Point(0,0));
    Mat pozaCuContururi=Mat::zeros(poza2.size(),CV_8UC3);
    for(size_t i=0;i<contours.size();i++)
    {
        Scalar color= Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(pozaCuContururi,contours,i,color,2,8,hierarchy,0,Point());
    }
    gasesteContururiSiDreptunghi(pozaCuContururi);
}

void MainWindow:: gasesteContururiSiDreptunghi(const Mat&poza2)
{

    vector<Rect> boundRect(contours.size());
    for( size_t i=0;i<contours.size();i++)
        boundRect[i]=boundingRect(contours[i]);
    Mat pozaCuDreptunghiuriSiContururi=Mat::zeros(poza2.size(),CV_8UC3);
    for(size_t i=0;i<contours.size();i++)
    {
        Scalar color= Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        drawContours(pozaCuDreptunghiuriSiContururi,contours,i,color,2,8,hierarchy,0,Point());
        rectangle(pozaCuDreptunghiuriSiContururi,boundRect[i].tl(),boundRect[i].br(),color,2,8,0);
    }
    namedWindow("Poza cu dreptunghiuri si contururi",CV_WINDOW_AUTOSIZE);
    imshow("Poza cu dreptunghiuri si contururi",pozaCuDreptunghiuriSiContururi);
}

