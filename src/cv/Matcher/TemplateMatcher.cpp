#include"TemplateMatcher.h"


TemplateMatcher::TemplateMatcher(const Mat& srcImage, const Mat& templateImage)
    : m_srcImage(srcImage), m_templateImage(templateImage)
{
    initTemplateMatcher();
}

void TemplateMatcher::initTemplateMatcher()
{
    if (m_templateImage.empty()
        || m_srcImage.empty())
    {
        throw std::runtime_error("TemplateMatcher::initTemplateMatcher() - Template or src image is empty");
    }
    if (m_templateImage.rows > m_srcImage.rows
        || m_templateImage.cols > m_srcImage.cols)
    {
        throw std::runtime_error("TemplateMatcher::initTemplateMatcher() - Template image is bigger than src image");
    }

    cvtColor(m_srcImage, m_srcGray, COLOR_BGR2GRAY);
    cvtColor(m_templateImage, m_templateGray, COLOR_BGR2GRAY);

    m_templateH = m_templateGray.rows;
    m_templateW = m_templateGray.cols;
}

Mat TemplateMatcher::drawMatchResult() const
{
    Mat resultImage = m_srcImage.clone();
    if (m_bestMatchLoc.x< 0
        || m_bestMatchLoc.y<0)
    {
        return resultImage;
    }
    Point bottomRight(m_bestMatchLoc.x + m_templateW, m_bestMatchLoc.y + m_templateH);
    rectangle(resultImage, m_bestMatchLoc, bottomRight, Scalar(0, 0, 255), 2);

    return resultImage;
}

double TemplateMatcher::getBestSore() const
{
    return m_bestScore;
}

Point TemplateMatcher::getBestMatchLoc() const
{
    return m_bestMatchLoc;
}
