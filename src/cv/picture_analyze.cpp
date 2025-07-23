#include "picture_analyze.h"
#include <opencv2/imgproc.hpp>

picture_analyze::picture_analyze()
{
}

picture_analyze::~picture_analyze()
{
}

int picture_analyze::CVMat2QImage(Mat bgrmat, QImage &img)
{
    if( bgrmat.empty() )
    {
        return -1;
    }
    Mat rgb_mat, argb_mat;
    switch( bgrmat.type() )
    {
    case CV_8UC1:       //单通道
        img = QImage((const unsigned char *)bgrmat.data, bgrmat.cols, bgrmat.rows, bgrmat.step, QImage::Format_Grayscale8);
        break;
    case CV_8UC3:       //三通道BGR->RGB
        cvtColor(bgrmat, rgb_mat, cv::COLOR_BGR2RGB);
        img = QImage((const unsigned char *)rgb_mat.data, rgb_mat.cols, rgb_mat.rows, rgb_mat.step, QImage::Format_RGB888);
        //需要处理图像的颜色顺序？
        //OpenCV是BGR, QImage是RGB
        break;
    case CV_8UC4:       //四通道BGRA->RGBA
        cvtColor(bgrmat, argb_mat, cv::COLOR_BGRA2RGBA);
        img = QImage((const unsigned char *)bgrmat.data, bgrmat.cols, bgrmat.rows, bgrmat.step, QImage::Format_RGBA8888);
        break;
    default:
        break;
    }
}

int picture_analyze::QImage2CVMat(QImage img, Mat &mat)
{
    if( img.isNull() )
    {
        return -1;
    }
    switch( img.format() )
    {
    case QImage::Format_Grayscale8:
        mat = Mat(img.height(), img.width(), CV_8UC1, (void*)img.bits(), img.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = Mat(img.height(), img.width(), CV_8UC3, (void*)img.bits(), img.bytesPerLine());
        break;
    case QImage::Format_ARGB32:
        mat = Mat(img.height(), img.width(), CV_8UC4, (void*)img.bits(), img.bytesPerLine());
        break;
    default:
        break;
    }
}

