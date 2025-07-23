#include "OpenCV_Learn.h"
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

OpenCV::OpenCV()
{
    setWindowTitle("Zhang Graphics Open");
    resize(800, 600);
    initWidget();
    
    connect(btn_open, SIGNAL(clicked()), this, SLOT(slotBtnOpenClicked()));
    connect(btn_gray, SIGNAL(clicked()), this, SLOT(slotBtnGrayClicked()));
    connect(btn_reset, SIGNAL(clicked()), this, SLOT(slotBtnColorClicked()));
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
    btn_gray = new QPushButton("Grayscale");
    btn_reset = new QPushButton("Reset");
    ledit = new QLineEdit();
    scene = new QGraphicsScene();
    picture = new picture_analyze();
    grv->setScene(scene);

    glyt->addWidget(grv, 0, 0, 50, 50);
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
    //const QString *path2 = &path;
    //img_color.load(*path2);
    //img_gray = img_color.convertToFormat(QImage::Format_Grayscale8);

    const cv::String *path3 = &path.toStdString();


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
    const QString *path2 = &path;
    img_color.load(*path2);
    pix = QPixmap::fromImage(img_color);
    scene->addPixmap(pix);
}

void OpenCV::slotBtnOpenClicked()
{
    QFileDialog dlg(this);
    path = dlg.getOpenFileName(this, "Open Image", "", 
        "Image Files(*.png *.jpg *.bmp)");

    ledit->setText(path);

    if( !path.isEmpty() )
    {
        const std::string *path2 = &path.toStdString();
        color_mat = cv::imread(*path2, cv::IMREAD_COLOR);
        picture->CVMat2QImage(color_mat, img_color);
        QPixmap pix1 = QPixmap::fromImage(img_color);
        scene->clear();
        scene->addPixmap(pix1);
    }
}
