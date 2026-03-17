#include "OpenCV_Learn.h"
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <QMenuBar>
#include <QListWidget>
#include <QApplication>


OpenCV::OpenCV(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Zhang Graphics Open");
    resize(1200, 900);
    initWidget();
    initMDIWidget();
    initDockTabContainer();
    setDockNestingEnabled(true);

    m_WorkPosition_dockWdt = initDockWidget("WorkPositon>>>>");
    m_CameraConfig_dockWdt = initDockWidget("CameraSetup>>>>");
    m_Output_dockWdt = initDockWidget("Output>>>>");
    m_Strip_dockWdt = initDockWidget("Strip>>>>");

    //addDockWidget(Qt::LeftDockWidgetArea, m_WorkPosition_dockWdt);
    //addDockWidget(Qt::RightDockWidgetArea, m_CameraConfig_dockWdt);
    //addDockWidget(Qt::BottomDockWidgetArea, m_Output_dockWdt);
    //addDockWidget(Qt::BottomDockWidgetArea, m_Strip_dockWdt);

    //tabifyDockWidget(m_WorkPosition_dockWdt, m_WorkPosition_dockWdt);
    //tabifyDockWidget(m_CameraConfig_dockWdt, m_CameraConfig_dockWdt);
    //tabifyDockWidget(m_Output_dockWdt, m_Strip_dockWdt);

    //QDockWidget* m_leftDockWrapper = new QDockWidget(this);
    //m_leftDockWrapper->setFeatures(QDockWidget::DockWidgetFeature::DockWidgetVerticalTitleBar);
    //addDockWidget(Qt::LeftDockWidgetArea, m_leftDockWrapper);
    //QDockWidget *m_RightDockWrapper = new QDockWidget(this);
    //m_RightDockWrapper->setFeatures(QDockWidget::DockWidgetFeature::DockWidgetVerticalTitleBar);
    //addDockWidget(Qt::RightDockWidgetArea, m_RightDockWrapper);
    //QDockWidget *m_BottomDockWrapper = new QDockWidget(this);
    //m_BottomDockWrapper->setFeatures(QDockWidget::DockWidgetFeature::DockWidgetVerticalTitleBar);
    //addDockWidget(Qt::BottomDockWidgetArea, m_BottomDockWrapper);

    //m_leftDockWrapper->setWidget(m_DockTab_Left);
    //m_leftDockWrapper->setTitleBarWidget(new QWidget(m_leftDockWrapper));
    //m_leftDockWrapper->setTitleBarWidget(new QWidget(m_leftDockWrapper));
    //m_RightDockWrapper->setWidget(m_DockTab_Right);
    //m_RightDockWrapper->setTitleBarWidget(new QWidget(m_leftDockWrapper));
    //m_BottomDockWrapper->setWidget(m_DockTab_Bottom);
    //m_BottomDockWrapper->setTitleBarWidget(new QWidget(m_leftDockWrapper));

    //m_DockTab_Left->addDockTab("WorkPositon>>>>", m_WorkPosition_dockWdt);
    //m_DockTab_Right->addDockTab("CameraSetup>>>>", m_CameraConfig_dockWdt);
    //m_DockTab_Bottom->addDockTab("Output>>>>", m_Output_dockWdt);
    //m_DockTab_Bottom->addDockTab("Strip>>>>", m_Strip_dockWdt);

    initPlaceHoldeDocks(LeftArea);
    initPlaceHoldeDocks(RightArea);
    initPlaceHoldeDocks(BottomArea);

    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::West);
    setTabPosition(Qt::RightDockWidgetArea, QTabWidget::East);
    setTabPosition(Qt::BottomDockWidgetArea, QTabWidget::South);

    // ========== 3. 示例：为四个区域分别添加单个Dock（验证单个标签） ==========
    addDockToArea(m_WorkPosition_dockWdt, LeftArea, "");
    addDockToArea(m_CameraConfig_dockWdt, RightArea, "");
    addDockToArea(m_Output_dockWdt, BottomArea, "");
    addDockToArea(m_Strip_dockWdt, BottomArea, "");

    z_cv_lib = new Z_CV_lib();
    connect(btn_open, SIGNAL(clicked()), this, SLOT(slotBtnOpenClicked()));
    connect(btn_gray, SIGNAL(clicked()), this, SLOT(slotBtnGrayClicked()));
    connect(btn_reset, SIGNAL(clicked()), this, SLOT(slotBtnColorClicked()));
    connect(transparency, &QSlider::valueChanged, this, &OpenCV::slotSliderValueChanged);
    setStyleSheet(R"(
            /* 标签栏样式 */
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
            /* Dock整体样式 */
            QDockWidget {
                border: 1px solid #E0E0E0;
                margin: 2px;
            }
            /* Dock内容区间距 */
            QDockWidget > QWidget {
                padding: 8px;
            }
        )");
}

OpenCV::~OpenCV()
{
}

void OpenCV::initWidget()
{
    QWidget *central_wdt = new QWidget(this);
    glyt = new QGridLayout(central_wdt);
    grv = new QGraphicsView();
    btn_open = new QPushButton("Open");
    btn_gray = new QPushButton("Gray_scale");
    btn_reset = new QPushButton("Origin_scale");
    ledit = new QLineEdit();
    scene = new QGraphicsScene();
    picture = new picture_analyze();
    transparency = new QSlider();
    transparency->setRange(0, 100);
    transparency->setValue(100);
    transparency->setTickPosition(QSlider::TicksRight); // 刻度显示在滑块下方

    grv->setScene(scene);
    glyt->addWidget(grv, 0, 0, 50, 50);
    glyt->addWidget(transparency, 0, 50, 47, 1);
    glyt->addWidget(ledit, 50, 0, 1, 50);
    glyt->addWidget(btn_gray, 48, 50, 1, 1);
    glyt->addWidget(btn_reset, 49, 50, 1, 1);
    glyt->addWidget(btn_open, 50, 50, 1, 1);
    setCentralWidget(central_wdt);
}

void OpenCV::initMDIWidget()
{
    m_mdiArea = new QMdiArea(this);
    setCentralWidget(m_mdiArea);
    m_subWin_camera1 = new QMdiSubWindow(this);
    m_mdiArea->addSubWindow(m_subWin_camera1);

    QMenu* fileMenu = menuBar()->addMenu("文件");
    fileMenu->addAction("加载作业", this, SLOT(slot_LoadJob()));
    
    QMenu* cameraMenu = menuBar()->addMenu("设置");
    cameraMenu->addAction("相机设置", this, SLOT(slot_CameraConfig()));
    cameraMenu->addAction("网络设置", this, SLOT(slot_NetworkConfig()));
    
    QMenu* winMenu = menuBar()->addMenu("窗口");
    winMenu->addAction(tr("WorkPosition"), this, SLOT(slot_Win_WorkPosition()));
    winMenu->addAction(tr("CameraSetup"), this, SLOT(slot_Win_CameraConfig()));
    winMenu->addAction(tr("Output"), this, SLOT(slot_Win_Output()));
}

void OpenCV::initDockTabContainer()
{
    m_DockTab_Bottom = new ZDockTabContainer(0,this);
    m_DockTab_Left = new ZDockTabContainer(1,this);
    m_DockTab_Right = new ZDockTabContainer(2,this);
}

QDockWidget* OpenCV::initPlaceHoldeDocks(DockArea area)
{
    QDockWidget* dock = new QDockWidget(this);
    //dock->setVisible(false); // 隐藏占位
    dock->setWidget(new QWidget());
    dock->setMinimumSize(0, 0);
    dock->setMaximumSize(0, 0);
    dock->setEnabled(false);
    dock->setStyleSheet("background-color: transparent; border: none;");
    m_placeHolderDocks[area] = dock;
    return dock;
}

QDockWidget* OpenCV::initDockWidget(QString name)
{
    QDockWidget * WorkPosition_dockWdt = new QDockWidget(name, this);
    //addDockWidget(Qt::RightDockWidgetArea, m_WorkPosition_dockWdt);
    WorkPosition_dockWdt->setFeatures(QDockWidget::DockWidgetClosable 
        |QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable );
    WorkPosition_dockWdt->setFixedWidth(200);
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

void OpenCV::addDockToArea(QDockWidget* dock, DockArea area, const QString& contentText)
{
    QWidget* contentWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(contentWidget);
    layout->addWidget(new QLabel(contentText));
    dock->setWidget(contentWidget);

    QDockWidget* placeHolder = m_placeHolderDocks[area];
    QList<QDockWidget*>& dockList = m_areaDockLists[area];

    if (dockList.isEmpty()) 
    {
        this->addDockWidget(static_cast<Qt::DockWidgetArea>(area), placeHolder);
        this->tabifyDockWidget(placeHolder, dock);
        dock->raise();
    }
    else 
    {
        this->tabifyDockWidget(dockList.first(), dock);
    }

    dockList.append(dock);
    dock->setAllowedAreas(static_cast<Qt::DockWidgetArea>(area)); 

    QTabBar* tabBar = findChild<QTabBar*>();
    if (tabBar)
    {
        tabBar->setTabEnabled(0, false);
        tabBar->setStyleSheet(R"(
            /* 目标Dock的标签（索引0）正常显示 */
            QTabBar::tab:index(0) {
                padding: 8px 16px;
                background: #f0f0f0;
                border-radius: 4px 4px 0 0;
            }
            QTabBar::tab:index(0):selected {
                background: #ffffff;
                border: 1px solid #1989fa;
            }
            /* 空Dock的标签（索引1）完全隐藏 */
            QTabBar::tab:index(1) {
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

void OpenCV::slotBtnGrayClicked()
{
    if( path.isEmpty() )
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    if( origin_mat.channels()!=1 )
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
    if( path.isEmpty() )
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    picture->CVMat2QImage(origin_mat, img_color);
    pix = QPixmap::fromImage(img_color);
    scene->addPixmap(pix);
}

void OpenCV::slotSliderValueChanged(int value)
{
    if( path.isEmpty() )
    {
        QMessageBox::warning(this, "Warning", "Please Open Image First!");
        return;
    }
    if( origin_mat.channels()!=4 )
    {
        cvtColor(origin_mat, transparent_mat, COLOR_BGR2RGBA);
    }
    std::vector<cv::Mat> channels;
    cv::split(transparent_mat, channels);
    channels[3] = channels[3]*value/100;
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
}

void OpenCV::slot_NetworkConfig()
{
}

void OpenCV::slot_LoadJob()
{
    QString job_path = QApplication::applicationDirPath() + "/job/";
    QString job_file_path = QFileDialog::getOpenFileName(this, "Load Job", job_path, tr("Job Files(*.job)"));
    if (job_file_path.isEmpty())
    {
        return;
    }
    //TODO:加载作业
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
    m_CameraConfig_dockWdt->show();
}

void OpenCV::slotBtnOpenClicked()
{
    QFileDialog dlg(this);
    select_path = dlg.getOpenFileName(this, "Open Image", "",
        "Image Files(*.png *.jpg *.bmp)");

    if( !select_path.isEmpty() )
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
