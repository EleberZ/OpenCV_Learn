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
	QPushButton* btn;
	QLineEdit *ledit;
	QGraphicsScene* scene;
private slots:
	void slotBtnClicked();

};
