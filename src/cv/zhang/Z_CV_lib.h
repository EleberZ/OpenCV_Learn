#ifndef Z_CV_LIB_H
#define Z_CV_LIB_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

enum DenosingType
{
    GAUSSIAN,       //高斯滤波
    MEDIAN,       //中值滤波
    MEAN,           //均值滤波
    FOURIER_TRANSFORM,  //傅里叶变换, 频域低通
    WIENER,           //维纳滤波
    WAVELET,             //小波去噪
    ANISOTROPIC_DIFFUSION,  //各向异性扩散 
    TOTAL_VARIATION,     //总变差去噪
    NON_LOCAL_MEANS,     //非局部均值去噪
    BLOCK_MATCHING_3D,     //基于块匹配的去噪
    K_SVD,           //K-SVD去噪
    LOW_RANK,       //低秩去噪
    /*无监督学习方法降噪*/
    DnCNN,
};

template<typename srcT, typename dstT, typename Func>
struct has_return_compatible
{

#if __cplusplus == 201103L
private:
    template<typename F>
    static auto test(int) ->
        typename std::is_convertible<typename std::result_of<F(const srcT&)>::type, dstT>::type;
    template<typename F>
    static auto test(...)->std::false_type {}
#elif __cplusplus == 201402L
private:
    template<typename F>
    static auto test(int) ->
        typename std::is_convertible<typename std::result_of_t<F(const srcT&)>, dstT>::type;
    template<typename F>
    static auto test(...)->std::false_type {}
#elif __cplusplus == 201703L
private:
    template<typename F>
    static auto test(int) ->
        typename std::bool_constant<std::is_convertible_v<std::invoke_result_t<F, const srcT&>, dstT>>;
    template<typename F>
    static auto test(...) -> std::false_type { return false; }
#endif
public:
    static constexpr bool value = decltype(test<Func>(0))::value;
};

class Z_CV_lib
{
public:
    Z_CV_lib();
    ~Z_CV_lib();
    void BGRToGrayScala(const cv::Mat& src_mat, cv::Mat& dst_mat, cv::ColorConversionCodes code);
    /************************   day1   ************************/
    /*
    @brief: 遍历Mat矩阵的每个元素，并对其进行操作
    @param: mat - 输入的Mat矩阵
    @param: func - 指向操作函数的指针，操作函数的参数用于接收输入Mat矩阵，
        该函数将被应用于每个元素
    */

    void traverseMat(const cv::Mat& mat, std::function<void()> func);

    template <typename srcT, typename dstT, typename Func>
    inline std::enable_if<has_return_compatible<srcT, dstT, Func>::value, void>
        traverseMat(const cv::Mat& src_mat, cv::Mat& dst_mat, Func&& func)
    {
        // 检查
        //static_assert();

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

    template <typename srcT, typename dstT>
    void traverseMat(const cv::Mat& src_mat, cv::Mat& dst_mat, void (srcT, dstT))
    {

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
    /************************   day1   ************************/
    
    void image_grayscale(const cv::Mat& src_mat, cv::Mat& dst_mat); //灰度化
    void image_denoising(const cv::Mat& src_mat, cv::Mat& dst_mat, DenosingType denosing_type); //去噪
private:
    void image_grayscale_each_pixel(const cv::Mat& src_mat, cv::Mat& dst_mat);

    /************************   day1   ************************/

    /************************   day2   ************************/

    /************************   day2   ************************/


};

#endif // Z_CV_LIB_H


