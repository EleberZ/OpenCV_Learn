#ifndef MATCHALGORITHM_H
#define MATCHALGORITHM_H
#include <QString>
#include "opencv2/opencv.hpp"
//#include "YXEngine_global.h"
#include "opencv2/core.hpp"

class /*YXENGINE_EXPORT*/ MatchAlgorithm
{
public:
    MatchAlgorithm();
    void loadImage(const QString& img);
    void loadTemplate(const QString& file);
    void setMatching(int degree);
    void setRoi(int x,int y,int w,int h);
    void setMat(const cv::Mat& mat);
    void createTemplate(int x,int y,int w,int h,const QString& file);
    bool matchTemp(int &degree,QString &err);
private:
    double m_threshold;
    cv::Mat m_template;
    cv::Mat m_source;
    cv::Rect m_roi;
};

#endif // MATCHALGORITHM_H
