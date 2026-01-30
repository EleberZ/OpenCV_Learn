#include "matchalgorithm.h"
//#include "../yxengine.h"
#include <math.h>
#include <QObject>

MatchAlgorithm::MatchAlgorithm()
{
    m_threshold=0.01;
}
void MatchAlgorithm::loadImage(const QString& img)
{
    m_source.release();
    m_source = imread(img.toStdString(), cv::IMREAD_GRAYSCALE);
}
void MatchAlgorithm::loadTemplate(const QString& file)
{
    m_template = imread(file.toStdString(),cv::IMREAD_GRAYSCALE);
}
void MatchAlgorithm::setRoi(int x,int y,int w,int h)
{
    m_roi.x=x;
    m_roi.y=y;
    m_roi.width=w;
    m_roi.height=h;
}
void MatchAlgorithm::setMat(const cv::Mat& mat)
{
    m_source.release();
    m_source=mat.clone();
}
void MatchAlgorithm::createTemplate(int x,int y,int w,int h,const QString& file)
{
    if(!m_source.data) return;
    cv::Mat temp;
    temp = m_source(cv::Rect(x, y, w, h));
    m_template = temp.clone();
    imwrite(file.toStdString(),m_template);
}
void MatchAlgorithm::setMatching(int degree)
{
    m_threshold=0.1-(double)degree/1000.0;
}
bool MatchAlgorithm::matchTemp(int &degree,QString &err)
{
    //if(!ENGINE->isInitialized()) return true;
    if(!m_source.data)
    {
        err=QObject::tr("No images loaded");
        return false;
    }
    if(!m_template.data)
    {
        err=QObject::tr("The template image not loaded");
        return false;
    }
    if(m_roi.width<m_template.cols
            || m_roi.height<m_template.rows
            || (m_roi.width+m_roi.x)>m_source.cols
            || (m_roi.height+m_roi.y)>m_source.rows
            || m_roi.x<0
            || m_roi.y<0)
    {
        err=QObject::tr("ROI is not suitable");
        return false;
    }
    cv::Mat image;
    image = m_source(m_roi);
    if(!image.data)
    {
        err=QObject::tr("ROI is not suitable");
        return false;
    }
    cv::Mat temp = m_template;
    int width = m_source.cols - image.cols + 1;
    int height = m_source.rows - image.rows + 1;
    if(width<1 || height<1)
    {
        err=QObject::tr("Source image too small");
        return false;
    }
    cv::Mat result(width, height, CV_32FC1);
    matchTemplate(image, temp, result, cv::TM_SQDIFF_NORMED);
    double min, max;
    cv::Point min_location, max_location;
    minMaxLoc(result, &min, &max, &min_location, &max_location);
    degree=100-1000*min;
    if(degree<0) degree=0;
    if(min-m_threshold<0.001)
    {
        return true;
    }
    else
    {
        err=QObject::tr("The matching degree is less than the set value");
        return false;
    }
}
