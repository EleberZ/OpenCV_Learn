#ifndef PICTURE_ANALYZE_H
#define PICTURE_ANALYZE_H

#include <opencv2/core.hpp>
#include <QImage>
 
using namespace cv;

/*
QImage和 OpenCV 都有自己定义的图像格式，它们之间并不是一一对应的，但你可以将一些常见的 QImage::Format 转换为相应的OpenCV图像类型（cv::Mat）。
以下是一些常见的 QImage::Format 和它们对应的 OpenCV 图像类型：
1.QImage::Format_Mono(1-bit per pixel, binary image)
    - 对应的 OpenCV 类型: CV_8UC1 (但需要特殊处理，因为OpenCV不直接支持1位图像)

2.QImage::Format_MonoLSB(1-bit per pixel, binary image with least significant bit first)
    - 对应的 OpenCV 类型:CV_8UC1(同样需要特殊处理)

3.QImage::Format_Indexed8(8-bit per pixel, color indexed)
    - 对应的 OpenCV 类型:CV_8UC1(颜色索引需要单独处理)

4.QImage::Format_RGB32(8-bit per pixel, 4 channels - RGBA)
    - 对应的 OpenCV 类型:CV_8UC4(注意 OpenCV 使用 BGR 颜色顺序)

5.QImage::Format_ARGB32(8-bit per pixel, 4 channels - ARGB)
    - 对应的 OpenCV 类型:CV_8UC4(注意 OpenCV 使用 BGR 颜色顺序)

6.QImage::Format_ARGB32_Premultiplied(8-bit per pixel, 4 channels - ARGB with premultiplied alpha)
    - 对应的 OpenCV 类型:CV_8UC4(注意 OpenCV 使用 BGR 颜色顺序)

7.QImage::Format_RGB16(5-bit per pixel for red and blue, 6-bit per pixel for green)
    - 对应的 OpenCV 类型:CV_16UC3(但颜色通道的位数不同)

8.QImage::Format_RGB888(8-bit per pixel, 3 channels - RGB)
    - 对应的 OpenCV 类型:CV_8UC3(注意 OpenCV 使用 BGR 颜色顺序)

9.QImage::Format_Grayscale8(8-bit per pixel, grayscale)
    - 对应的 OpenCV 类型:CV_8UC1

10.QImage::Format_Grayscale16(16-bit per pixel, grayscale)
    - 对应的 OpenCV 类型:CV_16UC1

11.QImage::Format_RGBX8888(8-bit per pixel, 4 channels - RGBX)
    - 对应的 OpenCV 类型:CV_8UC4(注意 OpenCV 使用 BGR 颜色顺序)

12.QImage::Format_RGBA8888(8-bit per pixel, 4 channels - RGBA)
    - 对应的 OpenCV 类型:CV_8UC4(注意 OpenCV 使用 BGR 颜色顺序)

13.QImage::Format_RGBA8888_Premultiplied(8-bit per pixel, 4 channels - RGBA with premultiplied alpha)
    - 对应的 OpenCV 类型:CV_8UC4(注意 OpenCV 使用 BGR 颜色顺序)

14.QImage::Format_RGBX64(16-bit per pixel, 4 channels - RGBX)
    - 对应的 OpenCV 类型:CV_16UC4(注意 OpenCV 使用 BGR 颜色顺序)

15.QImage::Format_RGBA64(16-bit per pixel, 4 channels - RGBA)
    - 对应的 OpenCV 类型:CV_16UC4(注意 OpenCV 使用 BGR 颜色顺序)

16.QImage::Format_RGBA64_Premultiplied(16-bit per pixel, 4 channels - RGBA with premultiplied alpha)
    - 对应的 OpenCV 类型:CV_16UC4(注意 OpenCV 使用 BGR 颜色顺序)

请注意，当转换图像时，颜色顺序可能需要调整，因为 OpenCV 使用 BGR 颜色顺序，而 QImage 使用 RGB 颜色顺序。你可以使用 OpenCV 的cv::cvtColor函数来转换颜色顺序。例如，如果你有一个QImage::Format_RGB888格式的图像，你可以使用cv::cvtColor将其从 RGB 转换为 BGR。
以下是一个示例代码，展示如何将QImage转换为cv::Mat并调整颜色顺序：

#include <QImage>
#include <opencv2/opencv.hpp>

cv::Mat QImageToMat(const QImage& image) {
    // 将 QImage 转换为 cv::Mat
    cv::Mat mat(image.height(), image.width(), CV_8UC3, const_cast<uchar*>(image.bits()), image.bytesPerLine());
    // 调整颜色顺序从 RGB 到 BGR
    cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
    return mat;
}
在这个示例中，我们首先将QImage转换为cv::Mat，然后使用cv::cvtColor函数将颜色顺序从 RGB 调整为 BGR。这样，你就可以在 OpenCV 中使用转换后的cv::Mat对象了。
*/

class picture_analyze
{
public:
	picture_analyze();
	~picture_analyze();
	int CVMat2QImage(Mat mat, QImage& pixmap);
	int QImage2CVMat(QImage pixmap, Mat& mat);




private:
	Mat rgbmat;
};

#endif // !PICTURE_ANALYZE_H
