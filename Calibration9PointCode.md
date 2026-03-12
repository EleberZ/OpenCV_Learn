以下是完整的 C++ 九点标定实现：

## 方法一：单应性矩阵（推荐）

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

class NinePointCalibrator {
public:
    cv::Mat H;         // 单应性矩阵
    double meanError;  // 平均重投影误差

    // 执行标定
    bool calibrate(const std::vector<cv::Point2f>& imagePoints,
                   const std::vector<cv::Point2f>& worldPoints)
    {
        if (imagePoints.size() != 9 || worldPoints.size() != 9) {
            std::cerr << "需要恰好9对点!" << std::endl;
            return false;
        }

        // 计算单应性矩阵（图像坐标 -> 世界坐标）
        // method=0: 普通最小二乘，所有点参与计算
        H = cv::findHomography(imagePoints, worldPoints, 0);

        if (H.empty()) {
            std::cerr << "单应性矩阵计算失败!" << std::endl;
            return false;
        }

        // 计算重投影误差
        meanError = computeError(imagePoints, worldPoints);
        std::cout << "标定完成，平均误差: " << meanError << std::endl;
        return true;
    }

    // 像素坐标 -> 世界坐标
    cv::Point2f pixelToWorld(const cv::Point2f& pixel) const {
        std::vector<cv::Point2f> src = { pixel };
        std::vector<cv::Point2f> dst;
        cv::perspectiveTransform(src, dst, H);
        return dst[0];
    }

    // 世界坐标 -> 像素坐标
    cv::Point2f worldToPixel(const cv::Point2f& world) const {
        cv::Mat H_inv = H.inv();
        std::vector<cv::Point2f> src = { world };
        std::vector<cv::Point2f> dst;
        cv::perspectiveTransform(src, dst, H_inv);
        return dst[0];
    }

    // 保存标定结果
    void save(const std::string& path) const {
        cv::FileStorage fs(path, cv::FileStorage::WRITE);
        fs << "homography" << H;
        fs << "mean_error" << meanError;
        fs.release();
        std::cout << "标定数据已保存至: " << path << std::endl;
    }

    // 加载标定结果
    bool load(const std::string& path) {
        cv::FileStorage fs(path, cv::FileStorage::READ);
        if (!fs.isOpened()) return false;
        fs["homography"] >> H;
        fs["mean_error"] >> meanError;
        fs.release();
        return true;
    }

private:
    double computeError(const std::vector<cv::Point2f>& imagePoints,
                        const std::vector<cv::Point2f>& worldPoints)
    {
        double totalError = 0.0;
        for (size_t i = 0; i < imagePoints.size(); i++) {
            cv::Point2f predicted = pixelToWorld(imagePoints[i]);
            double dx = predicted.x - worldPoints[i].x;
            double dy = predicted.y - worldPoints[i].y;
            double err = std::sqrt(dx * dx + dy * dy);
            totalError += err;
            std::cout << "  点" << i << ": 预测(" << predicted.x << ", " << predicted.y
                      << ")  实际(" << worldPoints[i].x << ", " << worldPoints[i].y
                      << ")  误差=" << err << std::endl;
        }
        return totalError / imagePoints.size();
    }
};
```

---

## 方法二：最小二乘仿射变换

```cpp
// 用全部9点做最小二乘仿射拟合（无透视畸变时更稳定）
cv::Mat getAffineMatrixLstSq(const std::vector<cv::Point2f>& src,
                              const std::vector<cv::Point2f>& dst)
{
    int n = (int)src.size();
    cv::Mat A(2 * n, 6, CV_64F, cv::Scalar(0));
    cv::Mat b(2 * n, 1, CV_64F);

    for (int i = 0; i < n; i++) {
        // 行 2i:   [x, y, 1, 0, 0, 0] * [a,b,c,d,e,f]^T = dst_x
        A.at<double>(2*i, 0) = src[i].x;
        A.at<double>(2*i, 1) = src[i].y;
        A.at<double>(2*i, 2) = 1.0;
        b.at<double>(2*i)    = dst[i].x;

        // 行 2i+1: [0, 0, 0, x, y, 1] * [a,b,c,d,e,f]^T = dst_y
        A.at<double>(2*i+1, 3) = src[i].x;
        A.at<double>(2*i+1, 4) = src[i].y;
        A.at<double>(2*i+1, 5) = 1.0;
        b.at<double>(2*i+1)    = dst[i].y;
    }

    // 最小二乘求解: params = (A^T A)^{-1} A^T b
    cv::Mat params;
    cv::solve(A, b, params, cv::DECOMP_SVD);

    // 构造 2x3 仿射矩阵
    cv::Mat M = (cv::Mat_<double>(2, 3) 
        params.at<double>(0), params.at<double>(1), params.at<double>(2),
        params.at<double>(3), params.at<double>(4), params.at<double>(5));

    return M;
}

// 仿射变换：点转换
cv::Point2f applyAffine(const cv::Point2f& pt, const cv::Mat& M) {
    cv::Mat src = (cv::Mat_<double>(3, 1) << pt.x, pt.y, 1.0);
    cv::Mat dst = M * src;
    return cv::Point2f((float)dst.at<double>(0), (float)dst.at<double>(1));
}
```

---

## 完整 main 示例

```cpp
int main() {
    // ── 1. 定义9个标定点 ──────────────────────────────
    // 图像坐标（像素）- 3x3 均匀分布
    std::vector<cv::Point2f> imagePoints = {
        {100, 100}, {400, 100}, {700, 100},
        {100, 400}, {400, 400}, {700, 400},
        {100, 700}, {400, 700}, {700, 700}
    };

    // 对应世界坐标（mm）
    std::vector<cv::Point2f> worldPoints = {
        {  0,   0}, {150,   0}, {300,   0},
        {  0, 150}, {150, 150}, {300, 150},
        {  0, 300}, {150, 300}, {300, 300}
    };

    // ── 2. 单应性矩阵标定 ────────────────────────────
    NinePointCalibrator calib;
    if (!calib.calibrate(imagePoints, worldPoints)) {
        return -1;
    }

    std::cout << "\n单应性矩阵 H:\n" << calib.H << std::endl;

    // ── 3. 坐标转换测试 ──────────────────────────────
    cv::Point2f testPixel(400, 400);
    cv::Point2f world = calib.pixelToWorld(testPixel);
    std::cout << "\n像素(" << testPixel.x << ", " << testPixel.y
              << ") -> 世界(" << world.x << ", " << world.y << ")" << std::endl;

    cv::Point2f backPixel = calib.worldToPixel(world);
    std::cout << "反向验证: 世界(" << world.x << ", " << world.y
              << ") -> 像素(" << backPixel.x << ", " << backPixel.y << ")" << std::endl;

    // ── 4. 保存/加载标定结果 ─────────────────────────
    calib.save("calibration.yml");

    NinePointCalibrator calib2;
    calib2.load("calibration.yml");
    cv::Point2f world2 = calib2.pixelToWorld(testPixel);
    std::cout << "\n加载后转换: 像素(" << testPixel.x << ", " << testPixel.y
              << ") -> 世界(" << world2.x << ", " << world2.y << ")" << std::endl;

    // ── 5. 仿射变换方法对比 ───────────────────────────
    cv::Mat M = getAffineMatrixLstSq(imagePoints, worldPoints);
    std::cout << "\n仿射矩阵 M:\n" << M << std::endl;

    cv::Point2f affineResult = applyAffine(testPixel, M);
    std::cout << "仿射变换结果: (" << affineResult.x << ", " << affineResult.y << ")" << std::endl;

    return 0;
}
```

---

## CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(NinePointCalib)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)

add_executable(nine_point_calib main.cpp)
target_link_libraries(nine_point_calib ${OpenCV_LIBS})
```

---

## 关键说明

| 要点 | 说明 |
|------|------|
| `cv::findHomography` | `method=0` 使用全部点最小二乘，`RANSAC` 可剔除异常点 |
| `cv::perspectiveTransform` | 必须用 `vector<Point2f>` 输入，不能直接用单点 |
| 误差标准 | 工业场景一般要求平均误差 < 0.5mm |
| 点分布 | 9点需覆盖整个工作区域，避免外推误差 |
| 坐标系 | 图像Y轴向下，注意与机器人坐标系方向对齐 |