激光打标是九点标定最经典的应用场景！让我针对这个场景重新解释。

## 激光打标的具体问题

```
摄像头/视觉系统                    振镜控制器
                                  
看到工件在图像的                   需要告诉振镜：
某个像素位置                  →    打到哪个坐标
(pixel_x, pixel_y)               (galvo_x, galvo_y)
```

两个坐标系之间**不是简单的比例关系**，因为：
- 镜头畸变
- 振镜非线性
- 安装角度偏差
- 场镜畸变

所以需要标定。

---

## 激光打标标定的实际流程

```
第一步：打标                第二步：拍照               第三步：计算H
                           
振镜按9个已知坐标           摄像头拍下9个点             findHomography
在标定板上打9个点    →      的图像位置          →       得到矩阵H
                           
(galvo坐标已知)            (pixel坐标测量出来)
```

**注意方向**：你是用图像坐标找振镜坐标，所以：
- `src` = 图像像素坐标
- `dst` = 振镜控制坐标

---

## 针对激光打标的完整C++代码

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

class LaserMarkingCalibrator {
public:
    cv::Mat H;
    double meanError = 0.0;

    /**
     * 标定
     * @param cameraPoints  摄像头拍到的9个打标点的【像素坐标】
     * @param galvoPoints   对应的振镜【控制坐标】（你发给振镜的坐标）
     */
    bool calibrate(const std::vector<cv::Point2f>& cameraPoints,
                   const std::vector<cv::Point2f>& galvoPoints)
    {
        if (cameraPoints.size() < 9 || galvoPoints.size() < 9) {
            std::cerr << "至少需要9对点!" << std::endl;
            return false;
        }

        H = cv::findHomography(cameraPoints, galvoPoints, 0);

        if (H.empty()) {
            std::cerr << "标定失败，请检查点位是否共线!" << std::endl;
            return false;
        }

        // 打印误差
        computeAndPrintError(cameraPoints, galvoPoints);
        return true;
    }

    /**
     * 核心功能：给定工件在图像中的位置，返回应该发给振镜的坐标
     * @param cameraPoint  视觉识别到的像素坐标
     * @return             发给振镜的控制坐标
     */
    cv::Point2f cameraToGalvo(const cv::Point2f& cameraPoint) const {
        std::vector<cv::Point2f> src = { cameraPoint };
        std::vector<cv::Point2f> dst;
        cv::perspectiveTransform(src, dst, H);
        return dst[0];
    }

    // 反向：振镜坐标 -> 图像坐标（用于验证）
    cv::Point2f galvoToCamera(const cv::Point2f& galvoPoint) const {
        cv::Mat H_inv = H.inv();
        std::vector<cv::Point2f> src = { galvoPoint };
        std::vector<cv::Point2f> dst;
        cv::perspectiveTransform(src, dst, H_inv);
        return dst[0];
    }

    void save(const std::string& path) const {
        cv::FileStorage fs(path, cv::FileStorage::WRITE);
        fs << "H" << H;
        fs << "mean_error" << meanError;
        fs.release();
        std::cout << "标定文件已保存: " << path << std::endl;
    }

    bool load(const std::string& path) {
        cv::FileStorage fs(path, cv::FileStorage::READ);
        if (!fs.isOpened()) {
            std::cerr << "无法打开标定文件: " << path << std::endl;
            return false;
        }
        fs["H"] >> H;
        fs["mean_error"] >> meanError;
        fs.release();
        std::cout << "标定文件已加载，历史误差: " << meanError << std::endl;
        return true;
    }

private:
    void computeAndPrintError(const std::vector<cv::Point2f>& cameraPoints,
                               const std::vector<cv::Point2f>& galvoPoints)
    {
        std::cout << "\n=== 标定误差分析 ===" << std::endl;
        double total = 0.0;
        for (size_t i = 0; i < cameraPoints.size(); i++) {
            cv::Point2f predicted = cameraToGalvo(cameraPoints[i]);
            float dx = predicted.x - galvoPoints[i].x;
            float dy = predicted.y - galvoPoints[i].y;
            float err = std::sqrt(dx*dx + dy*dy);
            total += err;
            std::cout << "  点" << i << ":"
                      << " 预测振镜(" << predicted.x << ", " << predicted.y << ")"
                      << " 实际振镜(" << galvoPoints[i].x << ", " << galvoPoints[i].y << ")"
                      << " 误差=" << err << std::endl;
        }
        meanError = total / cameraPoints.size();
        std::cout << "平均误差: " << meanError << "  (振镜坐标单位)" << std::endl;
    }
};


int main() {
    LaserMarkingCalibrator calib;

    // ============================================================
    // 【标定阶段】实际使用时只做一次，结果存文件
    // ============================================================

    // Step1: 让振镜按这9个坐标打标（在标定板上打9个点）
    std::vector<cv::Point2f> galvoPoints = {
        {-3000, -3000}, {0, -3000}, {3000, -3000},  // 振镜坐标范围
        {-3000,     0}, {0,     0}, {3000,     0},  // 根据你的振镜实际范围修改
        {-3000,  3000}, {0,  3000}, {3000,  3000}   // 例如 ±4095 或 ±32767
    };

    // Step2: 用摄像头拍照，识别出9个打标点在图像中的像素位置
    // （这里用假数据演示，实际由你的视觉算法测量）
    std::vector<cv::Point2f> cameraPoints = {
        {112, 108}, {398,  95}, {689, 110},
        {108, 401}, {400, 400}, {692, 399},
        {115, 694}, {401, 695}, {690, 692}
    };

    // Step3: 执行标定
    if (!calib.calibrate(cameraPoints, galvoPoints)) {
        return -1;
    }

    // 保存标定结果（以后直接load，不用重新标定）
    calib.save("laser_calib.yml");


    // ============================================================
    // 【生产阶段】每次打标时使用
    // ============================================================

    // 加载标定文件（程序启动时执行一次）
    LaserMarkingCalibrator prod;
    prod.load("laser_calib.yml");

    // 视觉识别到工件LOGO中心在图像的像素位置
    cv::Point2f detectedPosition(350, 280);

    // 转换为振镜坐标，直接发给振镜控制器
    cv::Point2f galvoCmd = prod.cameraToGalvo(detectedPosition);
    std::cout << "\n=== 生产使用 ===" << std::endl;
    std::cout << "视觉识别像素坐标: (" << detectedPosition.x
              << ", " << detectedPosition.y << ")" << std::endl;
    std::cout << "发送振镜控制坐标: (" << galvoCmd.x
              << ", " << galvoCmd.y << ")" << std::endl;

    return 0;
}
```

---

## 你的实际操作步骤

```
第一次标定（换设备/移位后重做）：

1. 准备一块标定板（铝板/不锈钢板）

2. 在程序里设好 galvoPoints（9个振镜坐标）
   → 让振镜打出9个标记点

3. 用摄像头拍照，识别9个点的像素坐标
   → 填入 cameraPoints

4. 运行标定，查看误差是否达标
   → 保存 laser_calib.yml

─────────────────────────────

日常生产：

1. 加载 laser_calib.yml

2. 摄像头拍工件 → 视觉识别目标位置(像素)

3. cameraToGalvo() 转换

4. 发给振镜控制器打标
```

---

## 误差多少算合格

| 应用 | 误差要求 |
|------|---------|
| 普通打标（文字/图案） | < 0.1mm |
| 精密打标（电路板） | < 0.05mm |
| 超精密 | 需要更多标定点（如25点5×5） |

误差太大通常是因为：标定点分布不够均匀，或者识别像素坐标时不够准确。

你现在用的是什么振镜控制卡？不同的卡发送坐标的方式不一样，我可以帮你对接那部分代码。