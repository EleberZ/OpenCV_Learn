#include "NinePoint.h"

//九点标定为求解超定方程组。

//赋值
Point2D Point2D::operator=(const Point2D& p) const
{
	return Point2D(p.m_x, p.m_y);
}

//减法
Point2D Point2D::operator-(const Point2D& p) const
{
	return Point2D(m_x - p.m_x, m_y - p.m_y);
}

//外积
Point2D Point2D::operator*(const Point2D& p) const
{
	return Point2D(m_x * p.m_x, m_y * p.m_y);
}



Calibration::Calibration()
    : isCalibrated(false)
{

}

Calibration::~Calibration()
{
}

bool Calibration::calibrate()
{
	if (m_pixl_points.size() >= 9)
	{
		return false;
	}
	int pixl_point_count = m_pixl_points.size();
	//2X3矩阵的个数=像素点的个数
	std::vector<std::vector<double>> A(2 * pixl_point_count, std::vector<double>(6, 0));	
	std::vector<double> B(2 * pixl_point_count, 0);
}


