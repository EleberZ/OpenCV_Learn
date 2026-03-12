#ifndef NINE_POINT_CALIBRATION_H
#define NINE_POINT_CALIBRATION_H

#include <vector>

/*
九点标定求解的是一个2×3 的仿射变换矩阵

*/

struct Point2D
{
	double m_x;
	double m_y;
	Point2D(double x, double y): m_x(x), m_y(y) {}
};

class Calibration
{
public:
	Calibration();
	~Calibration();

private:

	bool addCalibPoint(const Point2D& pixl_point, Point2D& mechanical_point);		//添加标定点
	bool calibrate();		//求解仿射变换矩阵
    std::vector<Point2D> m_pixl_points;		//像素坐标点
    std::vector<Point2D> m_mechanical_points;	//机械坐标点
	std::vector<double> m_target_matrix;		//仿射变换矩阵(X, Y方向的缩放系数, X,Y的旋转与剪切系数， X,Y方向的平移)
	bool isCalibrated;		
};

#endif