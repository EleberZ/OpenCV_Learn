#ifndef Z_CV_LIB_H
#define Z_CV_LIB_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

class Z_CV_lib
{
public:
    Z_CV_lib();
    ~Z_CV_lib();

    /************************   day1   ************************/
    /*
    @brief: 遍历Mat矩阵的每个元素，并对其进行操作
    @param: mat - 输入的Mat矩阵
    @param: func - 指向操作函数的指针，操作函数的参数用于接收输入Mat矩阵，
        该函数将被应用于每个元素
    */
    template <typename srcT, typename dstT, typename Func>
    void traverseMat(const cv::Mat& src_mat, cv::Mat& dst_mat, Func&& func);
    template <typename srcT, typename dstT>
    void traverseMat(const cv::Mat& mat, void (*func)(srcT, dstT));
    void traverseMat(const cv::Mat& mat, std::function<void()> func);

    /************************   day1   ************************/

    /************************   day2   ************************/

    /************************   day2   ************************/


};

template <typename srcT, typename dstT, typename Func>
inline void Z_CV_lib::traverseMat(const cv::Mat &src_mat, cv::Mat &dst_mat, Func &&func)
{
    // 检查
    static_assert();
    CV_Assert(!src_mat.empty() 
        && src_mat.type() == cv::DataType<srcT>::type
        && dst_mat.type() == cv::DataType<dstT>::type);

    dst_mat.create(src_mat.size(), src_mat.type());
    int cols = src_mat.cols;
    int rows = src_mat.rows;
    if (src_mat.isContinuous())
    {
        cols *= rows;
        rows = 1;
    }

    // 遍历每个元素并应用操作函数
    for (int i = 0; i < rows; i++)
    {
        const srcT* src_rowPtr = src_mat.ptr<srcT>(i);
        dstT* dst_rowPtr = dst_mat.ptr<dstT>(i);
        for (int j = 0; j < cols; j++)
        {
            std::forward<Func>(func)(src_rowPtr[j], dst_rowPtr[j]);
        }
    }
}

template<typename srcT, typename dstT>
inline void Z_CV_lib::traverseMat(const cv::Mat& mat, void(*func)(srcT, dstT))
{
    CV_Assert(!src_mat.empty()
        && src_mat.type() == cv::DataType<srcT>::type
        && dst_mat.type() == cv::DataType<dstT>::type);

    dst_mat.create(src_mat.size(), src_mat.type());
    int cols = src_mat.cols;
    int rows = src_mat.rows;
    if (src_mat.isContinuous())
    {
        cols *= rows;
        rows = 1;
    }

    // 遍历每个元素并应用操作函数
    for (int i = 0; i < rows; i++)
    {
        const srcT* src_rowPtr = src_mat.ptr<srcT>(i);
        dstT* dst_rowPtr = dst_mat.ptr<dstT>(i);
        for (int j = 0; j < cols; j++)
        {
            func(src_rowPtr[j], dst_rowPtr[j]);
        }
    }
}


#endif // Z_CV_LIB_H


