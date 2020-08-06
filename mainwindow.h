#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QQueue>
#include <QVector>
#include <QPixmap>
#include <QImage>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updatePixmaps();//更新陈列照片栏
    void initializeCamera();//初始化相机等设备
    void initializeLabel();//初始化相框

private slots:
    void slot_capture(int,QImage image);//截屏处理函数
    void on_pushButton_2_clicked();//shoot
    void on_pushButton_clicked();//open camera

private:
    Ui::MainWindow *ui;
    QCameraViewfinder* view;
    QCamera* camera;
    QCameraImageCapture* capture;
    QQueue<QString> paths;//存储前几次保存照片的路径
    QQueue<QPixmap> pixmaps;//存储前几次保存的照片，均以队列的数据结构存储，便于过滤早拍摄的照片，符合“先进先出”
    QVector<QLabel*> labels;//保存相框（QLabel）的索引，便于用循环控制所有相框
    QString pathfile;//存储前几次保存照片的路径的txt文件所在的路径
};
#endif // MAINWINDOW_H
