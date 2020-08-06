#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    initializeCamera();
    ui->setupUi(this); 
    ui->verticalLayout->insertWidget(0,view);
    initializeLabel();
    updatePixmaps();
}

void MainWindow::initializeCamera()
{
    view=new QCameraViewfinder(this);
    camera=new QCamera(this);
    capture=new QCameraImageCapture(camera);
    connect(capture,&QCameraImageCapture::imageCaptured,this,&MainWindow::slot_capture);
    camera->setViewfinder(view);
}

void MainWindow::initializeLabel()
{
    labels.push_back(ui->label);
    labels.push_back(ui->label_2);
    labels.push_back(ui->label_3);
    labels.push_back(ui->label_4);
    pathfile="D:/1 a project/camera/camera/res/path.txt";
    QFile pfile(pathfile);
    pfile.open(QIODevice::ReadWrite);
    QTextStream in(&pfile);
    for(int i=0;i<4;i++)
    {
        QString line = in.readLine();
        paths.enqueue(line);
    }
    for(int i=0;i<4;i++)
    {
        QPixmap pixmap(paths[i]);
        pixmaps.enqueue(pixmap);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
    delete capture;
    delete camera;
    QFile::remove(pathfile);
    QFile file(pathfile);
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);
    for(auto path:paths)
    {
        out<<path<<endl;
    }
}

void MainWindow::slot_capture(int,QImage image)
{
    camera->stop();   
    QMessageBox::StandardButton ifsave=QMessageBox::information(this,
        "save","want to save?",QMessageBox::Yes|QMessageBox::No);
    if(ifsave==QMessageBox::Yes)
    {
        QPixmap pixmap=QPixmap::fromImage(image);
        pixmaps.dequeue();
        pixmaps.enqueue(pixmap);
        updatePixmaps();
        QString path="D:/1 a project/camera/camera/res/capture"+QString::number(rand())+".png";
        QFile file(path);
        file.open(QIODevice::WriteOnly);
        if(pixmap.save(&file,"png",100))
        {
            paths.dequeue();
            paths.enqueue(path);
        }
    }
    camera->start();
}

void MainWindow::updatePixmaps()
{
    for(int i=0;i<4;i++)
    {
        labels[i]->setPixmap(pixmaps[i]);
    }
}

void MainWindow::on_pushButton_2_clicked()//shoot
{
    capture->capture();
}

void MainWindow::on_pushButton_clicked()
{

    delete ui->calendarWidget;
    camera->start();
}
