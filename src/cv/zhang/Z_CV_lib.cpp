#include "Z_CV_lib.h"

Z_CV_lib::Z_CV_lib()
{
}

Z_CV_lib::~Z_CV_lib()
{
}

void Z_CV_lib::BGRToGrayScala(const cv::Mat& src_mat, cv::Mat& dst_mat,
    cv::ColorConversionCodes code)
{
    //traverseMat<cv::Vec<uint8_t, 3>, uint8_t>(src_mat, dst_mat, 
    //    [](const cv::Vec<uint8_t, 3>src_element)->uint8_t
    //        {
    //            uint8_t dst_element;
    //            dst_element = src_element[0]*0.114 + src_element[1]*0.587 + src_element[2]*0.299;
    //            return dst_element;
    //        }
    //    );

}

void Z_CV_lib::traverseMat(const cv::Mat &mat, std::function<void()> func)
{
    
}
