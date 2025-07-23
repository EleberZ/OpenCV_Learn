// OpenCV_Learn.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QLineEdit>
#include "picture_analyze.h"
// TODO: 在此处引用程序需要的其他标头。

class OpenCV: public QMainWindow
{
	Q_OBJECT
public:
	OpenCV();
	~OpenCV();
	void initWidget();


private:
	QGridLayout* glyt;
	QGraphicsView* grv;
	QPushButton* btn_open,*btn_gray,*btn_reset;
	QLineEdit *ledit;
	QGraphicsScene* scene;
	QString path;
	QPixmap pix;
	QImage img_gray, img_color;
	cv::Mat gray_mat, color_mat;
	picture_analyze *picture;
private slots:
	void slotBtnOpenClicked();
	void slotBtnGrayClicked();
	void slotBtnColorClicked();

};
