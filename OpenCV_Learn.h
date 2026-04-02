#pragma once
#include "JobBlock.h"
#include "JobConfig.h"
#include "JobController.h"
#include "JobEditModel.h"
#include "JobTree.h"
#include "picture_analyze.h"
#include "Z_CV_lib.h"
#include "ZDockTabContainer.h"
#include <iostream>
#include <output_widget.h>
#include <QDockWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHash>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPushButton>
#include <QSlider>
#include"camer_config.h"

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
    void initTabBar();
    void initJob();
    void initGlobel();
	QDockWidget* initPlaceHoldeDocks(DockArea area);
	void initPlaceHoldeDocks();
	QDockWidget* initDockWidget(QString name);
	void addDockToArea(QDockWidget* dock, DockArea area, const QString& contentText);

    QSize WidgetShowAndHide(QWidget* widget, QSize size);
signals:
    void sglNewJob(QString job_file);
    void sglLoadJob(QString job_file);
    void sglSaveJob();
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
	void slot_NewJob();
	void slot_LoadJob();
	void slot_SaveJob();
	void slot_Win_WorkPosition();
	void slot_Win_Output();
	void slot_Win_CameraConfig();

private:
    QGridLayout *glyt;
    QGraphicsView *grv;
    QPushButton *btn_open, *btn_gray, *btn_reset;
    QLineEdit *ledit;
    QGraphicsScene *scene;
    QString path, select_path;
    QPixmap pix;
    QImage img_gray, img_color;
    cv::Mat gray_mat, origin_mat, transparent_mat;
    picture_analyze *picture;
    QSlider *transparency;
    Z_CV_lib *z_cv_lib;
    OutputWidget *output_wdt;
    QMdiArea *m_mdiArea;
    QDockWidget *m_WorkPosition_dockWdt;
    QDockWidget *m_CameraConfig_dockWdt;
    QDockWidget *m_Output_dockWdt;
    QDockWidget *m_Strip_dockWdt;
    QDockWidget *m_1_dockWdt;
    QDockWidget *m_2_dockWdt;
    QDockWidget *m_3_dockWdt;
    QDockWidget *m_4_dockWdt;
    QStringList m_strlist_dockWdt;


    QHash<int, QDockWidget> m_dockWidgetHash;
    QHash<int, QMdiSubWindow> m_subWinHash;
    QMdiSubWindow *m_subWin_camera1, *m_subWin_camera2;

    // 存储各区域的占位Dock（key：停靠区域，value：占位Dock）
    QMap<DockArea, QDockWidget *> m_placeHolderDocks;
    // 存储各区域的业务Dock列表（key：停靠区域，value：Dock列表）
    QMap<DockArea, QList<QDockWidget *>> m_areaDockLists;
    ZDockTabContainer *m_DockTab_Left;
    ZDockTabContainer *m_DockTab_Right;
    ZDockTabContainer *m_DockTab_Bottom;

    CameraConfig *m_camer_config;

    JobController *m_jobController;
    JobBlock *m_jobBlock;
    JobConfig *m_jobConfig;
    JobTree *m_jobTree;
    std::shared_ptr<JobEditModel> m_jobEditModel;
};
