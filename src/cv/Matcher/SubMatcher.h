#ifndef NORMEDCORRCOEFFMATCHER_H
#define NORMEDCORRCOEFFMATCHER_H

#include "TemplateMatcher.h"
#include <memory>

using namespace cv;


class NormedCorrCoeffMatcher : public TemplateMatcher
{
public:
    using TemplateMatcher::TemplateMatcher;
    void match() override;
};

class NormedSqDiffMatcher : public TemplateMatcher
{
public:
    using TemplateMatcher::TemplateMatcher;
    void match() override;
};

class NormedCorrMatcher : public TemplateMatcher
{
public:
    using TemplateMatcher::TemplateMatcher;
    void match() override;
};

class MatcherFactory
{
public:
    static unique_ptr<TemplateMatcher> createMatcher(const Mat& srcImage, const Mat& templateImage, MatchMethod method);
	MatcherFactory();
	~MatcherFactory();

private:

};


#endif // NORMEDCORRCOEFFMATCHER_H