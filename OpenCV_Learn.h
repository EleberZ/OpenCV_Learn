#pragma once
#include"camer_config.h"
#include "JobBlock.h"
#include "JobConfig.h"
#include "JobController.h"
#include "JobEditModel.h"
#include "JobTree.h"
#include "LogSystem.h"
#include "picture_analyze.h"
#include "Z_CV_lib.h"
#include "ZDockTabContainer.h"
#include <iostream>
#include <OutputWidget.h>
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
#include <QState>
#include <QStateMachine>

enum StateEnum
{
    Init,
    Ready,
    Work,
    Done,
    Alarm
};

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
    void initOutput();
    void initGlobel();
    void initHSM();
    void initLogAndOutput();
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
    void slotStart(bool clicked);
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
    void slot_JobTree_BlockDoubleClicked(QTreeWidgetItem *item);
    void slot_JobTree_AddBlock(int index);
    void slot_JobTree_CopyBlock(int index);
    void slot_JobTree_DeleteBlock(int index);

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
    QDockWidget *m_BlockConfig_dockWdt;
    QDockWidget *m_Output_dockWdt;
    QDockWidget *m_Strip_dockWdt;
    QStringList m_strlist_dockWdt;

    QHash<int, QDockWidget> m_dockWidgetHash;
    QHash<int, QMdiSubWindow> m_subWinHash;
    QMdiSubWindow *m_subWin_camera1, *m_subWin_camera2;

    // 存储各区域的占位Dock（key：停靠区域，value：占位Dock）
    QMap<DockArea, QDockWidget *> m_placeHolderDocks;
    // 存储各区域的业务Dock列表（key：停靠区域，value：Dock列表）
    QMap<DockArea, QList<QDockWidget *>> m_areaDockLists;

    CameraConfig *m_camer_config;

    JobController *m_jobController;
    JobBlock *m_jobBlock;
    JobConfig *m_jobConfig;
    JobTree *m_jobTree;
    std::shared_ptr<JobEditModel> m_jobEditModel;

    OutputWidget *m_output;
    LogSystem *m_log_system;

    QStateMachine *m_stateMachine;
    QState *m_state_Pconfig, *m_state_PRun, *m_state_PStop;
    QState *m_state_ready, *m_state_init, *m_state_work, *m_state_done, *m_state_alarm;

    QAction *toolbar_action_start;
    static StateEnum m_state;
};
