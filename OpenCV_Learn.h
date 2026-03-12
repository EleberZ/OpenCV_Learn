// OpenCV_Learn.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。
#pragma once

#include "picture_analyze.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include "Z_CV_lib.h"
#include <output_widget.h>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDockWidget>
#include <QHash>
#include <QLabel>
#include "ZDockTabContainer.h"


class OpenCV: public QMainWindow
{
	Q_OBJECT
public:
	enum DockArea {
		LeftArea = Qt::LeftDockWidgetArea,
		RightArea = Qt::RightDockWidgetArea,
		TopArea = Qt::TopDockWidgetArea,
		BottomArea = Qt::BottomDockWidgetArea
	};
	OpenCV(QWidget *parent = nullptr);
	~OpenCV();
	void initWidget();
	void initMDIWidget();
	void initDockTabContainer();
	QDockWidget* initPlaceHoldeDocks(DockArea area);
	void initPlaceHoldeDocks();
	QDockWidget* initDockWidget(QString name);
	void addDockToArea(QDockWidget* dock, DockArea area, const QString& contentText);



private:
	QGridLayout* glyt;
	QGraphicsView* grv;
	QPushButton* btn_open,*btn_gray,*btn_reset;
	QLineEdit *ledit;
	QGraphicsScene* scene;
	QString path, select_path;
	QPixmap pix;
	QImage img_gray, img_color;
	cv::Mat gray_mat, origin_mat, transparent_mat;
	picture_analyze *picture;
	QSlider *transparency;
	Z_CV_lib* z_cv_lib;
	OutputWidget* output_wdt;
    QMdiArea* m_mdiArea;
	QDockWidget* m_WorkPosition_dockWdt;
	QDockWidget* m_CameraConfig_dockWdt;
	QDockWidget* m_Output_dockWdt;
	QDockWidget* m_Strip_dockWdt;
	QDockWidget* m_1_dockWdt;
	QDockWidget* m_2_dockWdt;
	QDockWidget* m_3_dockWdt;
	QDockWidget* m_4_dockWdt;
	QStringList m_strlist_dockWdt;


	QHash<int, QDockWidget> m_dockWidgetHash;
	QHash<int, QMdiSubWindow> m_subWinHash;
	QMdiSubWindow *m_subWin_camera1, *m_subWin_camera2;

	// 存储各区域的占位Dock（key：停靠区域，value：占位Dock）
	QMap<DockArea, QDockWidget*> m_placeHolderDocks;
	// 存储各区域的业务Dock列表（key：停靠区域，value：Dock列表）
	QMap<DockArea, QList<QDockWidget*>> m_areaDockLists;
	ZDockTabContainer* m_DockTab_Left;
	ZDockTabContainer* m_DockTab_Right;
	ZDockTabContainer* m_DockTab_Bottom;
	
private slots:
	void slotBtnOpenClicked();
	void slotBtnGrayClicked();
	void slotBtnColorClicked();
	void slotSliderValueChanged(int value);
	void slot_createNewSubWindow();
	void slot_tileSubWindow();
	void slot_cascadeSubWindow();
	void slot_CameraConfig();
	void slot_NetworkConfig();
	void slot_LoadJob();
	void slot_Win_WorkPosition();
	void slot_Win_Output();
	void slot_Win_CameraConfig();

};
