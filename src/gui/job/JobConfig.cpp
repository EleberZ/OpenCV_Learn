#include "JobConfig.h"
#include <QHBoxLayout>

JobConfig::JobConfig(QWidget *parent)
    : JobEditViewImp(parent), m_job_block_name("Block*")
{
    setWindowTitle(m_job_block_name);
    initWidget();
    initConnect();
}

void JobConfig::initWidget()
{
    m_btn_save = new QPushButton(tr("Save"), this);
    m_gbox_main = new QGroupBox(m_job_block_name, this);
    m_cbox_job_mode = new QComboBox(this);
    m_cbox_job_mode->addItem(tr("Template Match"));
    m_template_match_method = new QComboBox(this);
    m_template_match_method->addItem(tr("SAD"));
    m_template_match_method->addItem(tr("SSD"));
    m_template_match_method->addItem(tr("NCC"));

    //m_gbox_path = new QGroupBox(tr("Path"), this);

    m_gbox_picture_show = new QGroupBox(tr("Picture Show"), this);
    QGridLayout *grid_layout = new QGridLayout(m_gbox_picture_show);

    m_ledit_roi_x = new QLineEdit(this);
    m_ledit_roi_y = new QLineEdit(this);
    m_ledit_roi_width = new QLineEdit(this);
    m_ledit_roi_height = new QLineEdit(this);

    m_graphic_scene_template = new QGraphicsScene(this);
    m_graphic_scene_mask = new QGraphicsScene(this);

    m_label_template_file = new QLabel(tr("Template File:"), this);
    m_ledit_template_file = new QLineEdit(this);
    m_graphic_view_template = new QGraphicsView(m_graphic_scene_template, this);
    m_check_enable_mask = new QCheckBox(tr("Mask Disable"), this);
    m_label_mask_file = new QLabel(tr("Mask File:"), this);
    m_ledit_mask_file = new QLineEdit(this);
    m_ledit_mask_file->setEnabled(false);
    m_graphic_view_mask = new QGraphicsView(m_graphic_scene_mask, this);
    m_graphic_view_mask->setEnabled(false);


    grid_layout->addWidget(new QLabel("ROI Origin", this), 0, 0, 1, 1);
    grid_layout->addWidget(new QLabel("X", this), 0, 1, 1, 1);
    grid_layout->addWidget(m_ledit_roi_x, 0, 2, 1, 2);
    grid_layout->addWidget(new QLabel("Y", this), 0, 4, 1, 1);
    grid_layout->addWidget(m_ledit_roi_y, 0, 5, 1, 2);

    grid_layout->addWidget(new QLabel("ROI Width(px)", this), 1, 0, 1, 1);
    grid_layout->addWidget(m_ledit_roi_width, 1, 1, 1, 6);

    grid_layout->addWidget(new QLabel("ROI Height(px)", this), 2, 0, 1, 1);
    grid_layout->addWidget(m_ledit_roi_height, 2, 1, 1, 6);

    grid_layout->addWidget(m_label_template_file, 3, 0, 1, 1);
    grid_layout->addWidget(m_ledit_template_file, 4, 0, 1, 7);
    grid_layout->addWidget(m_graphic_view_template, 5, 0, 7, 7);

    grid_layout->addWidget(m_label_mask_file, 12, 0, 1, 1);
    grid_layout->addWidget(m_check_enable_mask, 12, 1, 1, 6);
    grid_layout->addWidget(m_ledit_mask_file, 13, 0, 1, 7);
    grid_layout->addWidget(m_graphic_view_mask, 14, 0, 7, 7);

    QVBoxLayout *hbox = new QVBoxLayout(m_gbox_main);
    hbox->addWidget(m_cbox_job_mode);
    hbox->addWidget(m_template_match_method);
    hbox->addWidget(m_gbox_picture_show);
    hbox->addStretch();
    hbox->addWidget(m_btn_save);

    //组合页面
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    setLayout(main_layout);
    main_layout->addWidget(m_gbox_main);
    m_gbox_main->setLayout(hbox);
}

void JobConfig::updateWidget()
{
    
}

void JobConfig::initConnect()
{
    connect(m_check_enable_mask, &QCheckBox::toggled, this, &JobConfig::slotCheckEnableMask);
    connect(m_btn_save, &QPushButton::clicked, this, &JobConfig::sglBtnSave);
}

void JobConfig::setMainGroubBoxTitle(const QString &title)
{
    m_job_block_name = title;
    m_gbox_main->setTitle(title);
}

void JobConfig::slotJobBlockDoubleClicked(QTreeWidgetItem *item)
{
    QString name = item->text(0);
    setWindowTitle(name);
    m_gbox_main->setTitle(name);

}

void JobConfig::slotCheckEnableMask(bool ischeck)
{
    m_check_enable_mask->setText(ischeck ? tr("Mask Enable") : tr("Mask Disable"));
    m_ledit_mask_file->setEnabled(ischeck);
    m_graphic_view_mask->setEnabled(ischeck);
}

void JobConfig::slotNotifyJobEditView()
{
}

