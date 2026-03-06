#include "OpenCV_Learn.h"
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

OpenCV::OpenCV()
{
    setWindowTitle("Zhang Graphics Open");
    resize(800, 600);
    initWidget();
    z_cv_lib = new Z_CV_lib();
    connect(btn_open, SIGNAL(clicked()), this, SLOT(slotBtnOpenClicked()));
    connect(btn_gray, SIGNAL(clicked()), this, SLOT(slotBtnGrayClicked()));
    connect(btn_reset, SIGNAL(clicked()), this, SLOT(slotBtnColorClicked()));
    connect(transparency, &QSlider::valueChanged, this, &OpenCV::slotSliderValueChanged);
}

OpenCV::~OpenCV()
{
}

void OpenCV::initWidget()
{
    QWidget *central_wdt = new QWidget(this);
    glyt = new QGridLayout(central_wdt);
    grv = new QGraphicsView();
    btn_open = new QPushButton("Open");
    btn_gray = new QPushButton("Gray_scale");
    btn_reset = new QPushButton("Origin_scale");
    ledit = new QLineEdit();
    scene = new QGraphicsScene();
    picture = new picture_analyze();
    transparency = new QSlider();
    transparency->setRange(0, 100);
    transparency->setValue(100);
    transparency->setTickPosition(QSlider::TicksRight); // 刻度显示在滑块下方

    grv->setScene(scene);

    glyt->addWidget(grv, 0, 0, 50, 50);
    glyt->addWidget(transparency, 0, 50, 47, 1);
    glyt->addWidget(ledit, 50, 0, 1, 50);
    glyt->addWidget(btn_gray, 48, 50, 1, 1);
    glyt->addWidget(btn_reset, 49, 50, 1, 1);
    glyt->addWidget(btn_open, 50, 50, 1, 1);
    setCentralWidget(central_wdt);
}

void OpenCV::slotBtnGrayClicked()
{
    if( path.isEmpty() )
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    if( origin_mat.channels()!=1 )
    {
        //cvtColor(origin_mat, gray_mat, cv::COLOR_BGR2GRAY);
        z_cv_lib->BGRToGrayScala(origin_mat, gray_mat, COLOR_BGR2BGRA);
    }
    picture->CVMat2QImage(gray_mat, img_gray);
    pix = QPixmap::fromImage(img_gray);
    scene->addPixmap(pix);
}

void OpenCV::slotBtnColorClicked()
{
    if( path.isEmpty() )
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    picture->CVMat2QImage(origin_mat, img_color);
    pix = QPixmap::fromImage(img_color);
    scene->addPixmap(pix);
}

void OpenCV::slotSliderValueChanged(int value)
{
    if( path.isEmpty() )
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    if( origin_mat.channels()!=4 )
    {
        cvtColor(origin_mat, transparent_mat, COLOR_BGR2RGBA);
    }
    std::vector<cv::Mat> channels;
    cv::split(transparent_mat, channels);
    channels[3] = channels[3]*value/100;
    cv::merge(channels, transparent_mat);
    //cv::addWeighted
    picture->CVMat2QImage(transparent_mat, img_color);
    pix = QPixmap::fromImage(img_color);
    scene->addPixmap(pix);
}

void OpenCV::slotBtnOpenClicked()
{
    QFileDialog dlg(this);
    select_path = dlg.getOpenFileName(this, "Open Image", "",
        "Image Files(*.png *.jpg *.bmp)");

    if( !select_path.isEmpty() )
    {
        path = select_path;
        ledit->setText(path);
        std::string path2 = path.toStdString();
        origin_mat = cv::imread(path2, cv::IMREAD_UNCHANGED);
        picture->CVMat2QImage(origin_mat, img_color);
        QPixmap pix1 = QPixmap::fromImage(img_color);
        scene->clear();
        scene->addPixmap(pix1);
    }
}
