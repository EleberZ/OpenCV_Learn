#ifndef TEMPLATE_MATCHER_H
#define TEMPLATE_MATCHER_H

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

enum class MatchMethod
{
    TM_CCOEFF_NORMED,    // 归一化相关系数匹配（推荐）
    TM_CCORR_NORMED,     // 归一化相关匹配
    TM_SQDIFF_NORMED,    // 归一化平方差匹配
    TM_CCOEFF,           // 非归一化相关系数匹配
    TM_CCORR,            // 非归一化相关匹配
    TM_SQDIFF            // 非归一化平方差匹配
};

class TemplateMatcher
{
public:
	TemplateMatcher(const Mat& srcImage, const Mat &templateImage);
	virtual ~TemplateMatcher()=default;
protected:
    Mat m_srcImage;
    Mat m_templateImage;
    Mat m_srcGray;
    Mat m_templateGray;
    Mat m_matchResult;
    Point m_bestMatchLoc;
    double m_bestScore;
    int m_templateH;
    int m_templateW;
    void initTemplateMatcher();
    virtual void match() = 0;
    Mat drawMatchResult() const;
    double getBestSore()const;
    Point getBestMatchLoc()const;

    

private:

};


#endif  // TEMPLATE_MATCHER_H