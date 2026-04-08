#include "OpenCV_Learn.h"
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <QMenuBar>
#include <QListWidget>
#include <QApplication>
#include <QInputDialog>
#include <QToolButton>
#include <QSpacerItem>
#include <QFile>
#include <QToolBar>
#include <QAction>

StateEnum OpenCV::m_state = Init;
OpenCV::OpenCV(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Zhang Graphics Open");
    resize(1200, 900);
    initWidget();
    initMDIWidget();
    initDockTabContainer();
    setDockNestingEnabled(true);

    m_WorkPosition_dockWdt = initDockWidget("WorkPositon>>>>");
    m_WorkPosition_dockWdt->setFixedWidth(300);
    m_BlockConfig_dockWdt = initDockWidget("CameraSetup>>>>");
    m_BlockConfig_dockWdt->setFixedWidth(300);
    m_Output_dockWdt = initDockWidget("Output>>>>");
    m_Output_dockWdt->setFixedHeight(250);
    m_Strip_dockWdt = initDockWidget("Strip>>>>");
    m_Output_dockWdt->setFixedHeight(250);

    initPlaceHoldeDocks(LeftArea);
    initPlaceHoldeDocks(RightArea);
    initPlaceHoldeDocks(BottomArea);

    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::East);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::South);

    // ========== 3. 示例：为四个区域分别添加单个Dock（验证单个标签） ==========
    addDockToArea(m_BlockConfig_dockWdt, RightArea, "");
    addDockToArea(m_WorkPosition_dockWdt, LeftArea, "");
    addDockToArea(m_Output_dockWdt, BottomArea, "");
    addDockToArea(m_Strip_dockWdt, BottomArea, "");

    initTabBar();
    initJob();
    initGlobel();
    initOutput();
    initHSM();

    z_cv_lib = new Z_CV_lib();
    setStyleSheet(R"(
            QTabBar::tab {
                background-color: #F0F0F0;
                color: #333;
                padding: 8px 4px;
                margin: 1px;
            }
            QTabBar::tab:selected {
                background-color: #0078D7;
                color: white;
            }
            QDockWidget {
                border: 1px solid #E0E0E0;
                margin: 2px;
            }
            QDockWidget > QWidget {
                padding: 8px;
            }
        )");
}

OpenCV::~OpenCV()
{
    delete m_log_system;
    m_log_system = nullptr;
}

void OpenCV::initWidget()
{
    QWidget *central_wdt = new QWidget(this);
    glyt = new QGridLayout(central_wdt);
    grv = new QGraphicsView();
    //btn_open = new QPushButton("Open");
    //btn_gray = new QPushButton("Gray_scale");
    //btn_reset = new QPushButton("Origin_scale");
    //ledit = new QLineEdit();
    //scene = new QGraphicsScene();
    //picture = new picture_analyze();
    //transparency = new QSlider();
    //transparency->setRange(0, 100);
    //transparency->setValue(100);
    //transparency->setTickPosition(QSlider::TicksRight); // 刻度显示在滑块下方

    //grv->setScene(scene);
    //glyt->addWidget(grv, 0, 0, 50, 50);
    //glyt->addWidget(transparency, 0, 50, 47, 1);
    //glyt->addWidget(ledit, 50, 0, 1, 50);
    //glyt->addWidget(btn_gray, 48, 50, 1, 1);
    //glyt->addWidget(btn_reset, 49, 50, 1, 1);
    //glyt->addWidget(btn_open, 50, 50, 1, 1);
    QToolBar *bar = addToolBar("MainToolbar");
    bar->setFixedHeight(30);
    toolbar_action_start = bar->addAction(("Start"), this, OpenCV::slotStart);
    //toolbar_action->setIcon();
    bar->setStatusTip("Start the pocess");
    setCentralWidget(central_wdt);
}

void OpenCV::initMDIWidget()
{
    m_mdiArea = new QMdiArea(this);
    setCentralWidget(m_mdiArea);
    m_subWin_camera1 = new QMdiSubWindow(this);
    m_mdiArea->addSubWindow(m_subWin_camera1);

    QMenu *cameraMenu = menuBar()->addMenu(tr("Configure"));
    cameraMenu->addAction("相机设置", this, SLOT(slot_CameraConfig()));
    cameraMenu->addAction("网络设置", this, SLOT(slot_NetworkConfig()));

    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction("新建作业", this, SLOT(slot_NewJob()));
    fileMenu->addAction("加载作业", this, SLOT(slot_LoadJob()));
    fileMenu->addAction("保存作业", this, SLOT(slot_SaveJob()));

    QMenu *winMenu = menuBar()->addMenu(tr("WindowView"));
    winMenu->addAction(tr("WorkPosition"), this, SLOT(slot_Win_WorkPosition()));
    winMenu->addAction(tr("CameraSetup"), this, SLOT(slot_Win_CameraConfig()));
    winMenu->addAction(tr("Output"), this, SLOT(slot_Win_Output()));
    menuBar()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    //menuBar()->setFixedSize(200, 40);
}

void OpenCV::initDockTabContainer()
{
}

void OpenCV::initTabBar()
{
    QList<QTabBar *> list_tabBar = findChildren<QTabBar *>();
    for (QTabBar *tabBar : list_tabBar)
    {
        if (tabBar)
        {
            tabBar->setTabEnabled(0, false);
            tabBar->setStyleSheet(R"(
                /* 空Dock的标签完全隐藏 */
                QTabBar::tab:disabled {
                    width: 0px;    /* 宽度为0 */
                    height: 0px;   /* 高度为0 */
                    padding: 0px;  /* 内边距为0 */
                    margin: 0px;   /* 外边距为0 */
                    opacity: 0;    /* 完全透明 */
                }
            )");
            tabBar->setCurrentIndex(1);
        }
    }
}

void OpenCV::initJob()
{
    m_jobConfig = new JobConfig(this);
    m_jobTree = new JobTree(this);
    m_jobEditModel = std::make_shared<JobEditModel>(this);
    m_WorkPosition_dockWdt->setWidget(m_jobTree);
    m_BlockConfig_dockWdt->setWidget(m_jobConfig);

    //connect(this, &OpenCV::sglNewJob, m_jobEditModel.get(), &JobEditModel::slotNewJob);
    //connect(this, &OpenCV::sglLoadJob, m_jobEditModel.get(), &JobEditModel::slotLoadJob);
    //connect(this, &OpenCV::sglSaveJob, m_jobEditModel.get(), &JobEditModel::slotSaveJob);

    connect(m_jobTree, &JobTree::sglBlockDoubleClicked, m_jobConfig, &JobConfig::slotJobBlockDoubleClicked);
    connect(m_jobTree, &JobTree::sglBlockDoubleClicked, this, &OpenCV::slot_JobTree_BlockDoubleClicked);
    connect(m_jobConfig, &JobConfig::sglBtnSave, m_jobEditModel.get(), &JobEditModel::slotBlockSave);
}

void OpenCV::initGlobel()
{
    m_camer_config = new CameraConfig(this);
    m_camer_config->hide();
}

void OpenCV::initOutput()
{
    m_output = new OutputWidget(this);
    m_Output_dockWdt->setWidget(m_output);
    m_log_system = new LogSystem();
}

void OpenCV::initHSM()
{
    m_stateMachine = new QStateMachine(this);

    m_state_Pconfig = new QState(m_stateMachine);
    m_state_init = new QState(m_state_Pconfig);
    m_state_ready = new QState(m_state_Pconfig);

    m_state_PRun = new QState(m_stateMachine);
    m_state_work = new QState(m_state_PRun);
    m_state_done = new QState(m_state_PRun);

    m_state_PStop = new QState(m_stateMachine);
    m_state_alarm = new QState(m_state_PStop);

    m_state_init->setObjectName("Init");
    m_state_ready->setObjectName("Ready");
    m_state_init->addTransition(m_jobEditModel.get(), &JobEditModel::sglloadJobFileSuccess, m_state_ready);
    m_state_ready->addTransition(toolbar_action_start, &QAction::triggered, m_state_work);
    m_state_work->setObjectName("Work");
    m_state_done->setObjectName("Done");
    m_state_work->addTransition(toolbar_action_start, &QAction::triggered, m_state_ready);
    m_state_alarm->setObjectName("Alarm");
    m_state_PRun->addTransition(m_log_system, &LogSystem::sglAlarm, m_state_alarm);

    m_stateMachine->setInitialState(m_state_Pconfig);
    m_state_Pconfig->setInitialState(m_state_init);
    m_state_PRun->setInitialState(m_state_work);
    m_state_PStop->setInitialState(m_state_alarm);

    connect(m_state_init, &QState::entered, this, [this]()
        {
            m_state = Init;
            m_jobTree->setEnabled(false);
            m_jobConfig->setEnabled(false);
            m_output->appendText("System State:Init");
        });
    connect(m_state_ready, &QState::entered, this, [this]()
        {
            m_state = Ready;
            m_jobTree->setEnabled(true);
            m_jobConfig->setEnabled(true);
            m_jobTree->update();
            m_jobConfig->update();
            m_output->appendText("System State:Ready");
        });
    connect(m_state_work, &QState::entered, this, [this]()
        {
            m_state = Work;
            m_jobTree->setEnabled(false);
            m_jobConfig->setEnabled(false);
            m_output->appendText("System State:Work");
        });
    connect(m_state_done, &QState::entered, this, [this]()
        {
            m_state = Done;
            m_jobTree->setEnabled(false);
            m_jobConfig->setEnabled(false);
            m_output->appendText("System State:Done");
        });
    connect(m_state_alarm, &QState::entered, this, [this]()
        {
            m_state = Alarm;
            m_jobTree->setEnabled(false);
            m_jobConfig->setEnabled(false);
            m_output->appendText("System State:Alarm");
        });
    m_stateMachine->start();
}

QDockWidget *OpenCV::initPlaceHoldeDocks(DockArea area)
{
    QDockWidget *dock = new QDockWidget(this);
    dock->setWidget(new QWidget());
    dock->setMinimumSize(0, 0);
    dock->setMaximumSize(0, 0);
    dock->setEnabled(false);
    dock->setStyleSheet("background-color: transparent; border: none;");
    m_placeHolderDocks[area] = dock;
    return dock;
}

QDockWidget *OpenCV::initDockWidget(QString name)
{
    QDockWidget *WorkPosition_dockWdt = new QDockWidget(name, this);

    QWidget *titleBar = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(titleBar);
    layout->setContentsMargins(5, 5, 5, 5); // 紧凑一点
    layout->setSpacing(5);
    QLabel *titleLabel = new QLabel(name, this);
    titleLabel->setStyleSheet("font-weight: bold;");

    QToolButton *m_toggleBtn = new QToolButton(this);
    m_toggleBtn->setArrowType(Qt::DownArrow);
    m_toggleBtn->setFixedSize(16, 16);
    m_toggleBtn->setStyleSheet("QToolButton { border: none; } QToolButton:hover { background-color: #ccc; }");

    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addWidget(titleLabel);
    layout->addItem(spacer);
    layout->addWidget(m_toggleBtn);

    titleBar->setLayout(layout);
    WorkPosition_dockWdt->setTitleBarWidget(titleBar);
    connect(m_toggleBtn, &QToolButton::clicked, this, [WorkPosition_dockWdt]()
        {

        }
    );
    WorkPosition_dockWdt->setFeatures(QDockWidget::DockWidgetClosable
        | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    WorkPosition_dockWdt->setAcceptDrops(true);
    WorkPosition_dockWdt->setStyleSheet(R"(
        QDockWidget{
            background-color: #2E8000;
            border: 5px solid #0088FF;
            border-radius 4px;
            margin: 5px; 
        }
        QDockWidget::title{
            background-color: #2E86AB;
            color: white; 
            font-size: 14px;
        })"
    );
    return WorkPosition_dockWdt;
}

void OpenCV::addDockToArea(QDockWidget *dock, DockArea area, const QString &contentText)
{
    QWidget *contentWidget =  new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    layout->addWidget(new QLabel(contentText));
    dock->setWidget(contentWidget);

    QDockWidget *placeHolder = m_placeHolderDocks[area];
    QList<QDockWidget *> &dockList = m_areaDockLists[area];

    if (dockList.isEmpty())
    {
        this->addDockWidget(static_cast<Qt::DockWidgetArea>(area), placeHolder);
        this->tabifyDockWidget(placeHolder, dock);
    }
    else
    {
        this->tabifyDockWidget(dockList.first(), dock);
    }
    dockList.append(dock);
    dock->setAllowedAreas(static_cast<Qt::DockWidgetArea>(area));
}

QSize OpenCV::WidgetShowAndHide(QWidget *widget, QSize size)
{
    QSize temp;
    temp = widget->size();
    if (temp.height()==0
        &&temp.width()==0)
    {
        widget->setFixedSize(size);
    }
    else
    {
        widget->setFixedSize(0,0);
    }
    return temp;
}

void OpenCV::slotBtnGrayClicked()
{
    if (path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    if (origin_mat.channels() != 1)
    {
        cvtColor(origin_mat, gray_mat, cv::COLOR_BGR2GRAY);
        //z_cv_lib->BGRToGrayScala(origin_mat, gray_mat, COLOR_BGR2BGRA);
    }
    picture->CVMat2QImage(gray_mat, img_gray);
    pix = QPixmap::fromImage(img_gray);
    scene->addPixmap(pix);
}

void OpenCV::slotBtnColorClicked()
{
    if (path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    picture->CVMat2QImage(origin_mat, img_color);
    pix = QPixmap::fromImage(img_color);
    scene->addPixmap(pix);
}

void OpenCV::slotStart(bool clicked)
{
    if (m_state==StateEnum::Ready)
    {
        toolbar_action_start->setText("Stop");
    }
    else if (m_state==StateEnum::Work)
    {
        toolbar_action_start->setText("Start");
    }
}

void OpenCV::slotSliderValueChanged(int value)
{
    if (path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    if (origin_mat.channels() != 4)
    {
        cvtColor(origin_mat, transparent_mat, COLOR_BGR2RGBA);
    }
    std::vector<cv::Mat> channels;
    cv::split(transparent_mat, channels);
    channels[3] = channels[3] * value / 100;
    cv::merge(channels, transparent_mat);
    //cv::addWeighted
    picture->CVMat2QImage(transparent_mat, img_color);
    pix = QPixmap::fromImage(img_color);
    scene->addPixmap(pix);
}

void OpenCV::slot_createNewSubWindow()
{
}

void OpenCV::slot_tileSubWindow()
{
}

void OpenCV::slot_cascadeSubWindow()
{
}

void OpenCV::slot_CameraConfig()
{
    m_camer_config->show();
}

void OpenCV::slot_NetworkConfig()
{
}

void OpenCV::slot_NewJob()
{
    bool input_ok;
    QString job_path = QApplication::applicationDirPath() + "/job/";
    QString job_file = QInputDialog::getText(this, "New Job", "Job Name", QLineEdit::Normal, "", &input_ok);
    if (!input_ok)
    {
        return;
    }
    if (job_file.isEmpty())
    {
        QMessageBox::warning(this, "Warning", tr("Job File Name Can't be Empty!"));
    }
    else
    {
        QString job_file_path = job_path + job_file + ".job";
        QFile file(job_file_path);
        //emit sglNewJob(job_file_path);
        m_jobEditModel.get()->slotNewJob(job_file_path);
    }
}
void OpenCV::slot_LoadJob()
{
    QString job_path = QApplication::applicationDirPath() + "/job/";
    QString job_file_path = QFileDialog::getOpenFileName(this, "Load Job", job_path, tr("Job Files(*.job)"));
    if (job_file_path.isEmpty())
    { 
        return;
    }
    m_jobEditModel.get()->slotLoadJob(job_file_path);
    //emit sglLoadJob(job_file_path);
    //TODO:加载作业
}

void OpenCV::slot_SaveJob()
{
    m_jobEditModel.get()->slotSaveJob();
    //emit sglSaveJob();
}

void OpenCV::slot_Win_WorkPosition()
{
    m_WorkPosition_dockWdt->show();
}

void OpenCV::slot_Win_Output()
{
    m_Output_dockWdt->show();
}

void OpenCV::slot_Win_CameraConfig()
{
    m_BlockConfig_dockWdt->show();
}

void OpenCV::slot_JobTree_BlockDoubleClicked(QTreeWidgetItem *item)
{
    QString str = item->text(0);
    m_jobConfig->setMainGroubBoxTitle(str);
    m_BlockConfig_dockWdt->setWindowTitle(str);
}

void OpenCV::slotBtnOpenClicked()
{
    QFileDialog dlg(this);
    select_path = dlg.getOpenFileName(this, "Open Image", "",
        "Image Files(*.png *.jpg *.bmp)");

    if (!select_path.isEmpty())
    {
        path = select_path;
        ledit->setText(path);
        std::string path2 = path.toStdString();
        origin_mat = cv::imread(path2, cv::IMREAD_UNCHANGED);
        picture->CVMat2QImage(origin_mat, img_color);
        QPixmap pix1 = QPixmap::fromImage(img_color);
        scene->clear();
        scene->addPixmap(pix1);
    }
}
