#include "SubMatcher.h"

void NormedCorrCoeffMatcher::match()
{
    matchTemplate(m_srcGray, m_templateGray, m_matchResult, TM_CCOEFF_NORMED);
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(m_matchResult, &minVal, &maxVal, &minLoc, &maxLoc);
    m_bestMatchLoc = maxLoc;
    m_bestScore = maxVal;
}
void NormedSqDiffMatcher::match()
{
    matchTemplate(m_srcGray, m_templateGray, m_matchResult, TM_CCORR_NORMED);
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(m_matchResult, &minVal, &maxVal, &minLoc, &maxLoc);
    m_bestMatchLoc = maxLoc;
    m_bestScore = maxVal;
}

void NormedCorrMatcher::match()
{
    matchTemplate(m_srcGray, m_templateGray, m_matchResult, TM_SQDIFF_NORMED);
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(m_matchResult, &minVal, &maxVal, &minLoc, &maxLoc);
    m_bestMatchLoc = maxLoc;
    m_bestScore = maxVal;
}

unique_ptr<TemplateMatcher> MatcherFactory::createMatcher(const Mat& srcImage, const Mat& templateImage, MatchMethod method)
{
    switch (method)
    {
    case MatchMethod::TM_CCOEFF_NORMED:
    {
        return make_unique<NormedCorrCoeffMatcher>(srcImage, templateImage);
    }
    break;
    case MatchMethod::TM_CCORR_NORMED:
    {
        return make_unique<NormedCorrMatcher>(srcImage, templateImage);
    }
    break;
    case MatchMethod::TM_SQDIFF_NORMED:
    {
        return make_unique<NormedSqDiffMatcher>(srcImage, templateImage);
    }
    break;
    case MatchMethod::TM_CCOEFF:
    {

    }
    break;
    case MatchMethod::TM_CCORR:
    {

    }
    break;
    case MatchMethod::TM_SQDIFF:
    {

    }
    break;
    default:
        break;
    }

    return unique_ptr<TemplateMatcher>();
}

