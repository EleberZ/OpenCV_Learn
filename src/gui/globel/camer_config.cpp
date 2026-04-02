#include "camer_config.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QApplication>

CameraConfig::CameraConfig(QWidget *parent)
{
    setWindowTitle("Camera Config");
    initWidget();
    initModel();
    initConnect();
}
void CameraConfig::initWidget()
{
    setFixedSize(350, 450);
    setWindowModality(Qt::ApplicationModal);
    m_gbox_camera_config = new QGroupBox("Camera Config", this);
    m_gbox_connect_config = new QGroupBox("Connect Config", this);
    m_gbox_picture_config = new QGroupBox("Picture Config", this);

    m_ledit_camera_exposure_time = new QLineEdit("0", this);
    m_ledit_camera_ip = new QLineEdit("0.0.0.0", this);
    m_ledit_camera_ISO = new QLineEdit("0", this);
    m_ledit_template_path = new QLineEdit(QApplication::applicationDirPath() + "/template/", this);
    m_ledit_template_path->setEnabled(false);
    m_ledit_ok_path = new QLineEdit(QApplication::applicationDirPath() + "/history_picture/OK/", this);
    m_ledit_ok_path->setEnabled(false);
    m_ledit_ng_path = new QLineEdit(QApplication::applicationDirPath() + "/history_picture/NG/", this);
    m_ledit_ng_path->setEnabled(false);

    m_cbox_camera_connect_type = new QComboBox(this);
    m_cbox_camera_connect_type->addItem("USB");
    m_cbox_camera_connect_type->addItem("TCP/IP");
    m_cbox_camera_no = new QComboBox(this);
    m_cbox_camera_no->addItem("1");
    m_cbox_camera_no->addItem("2");
    m_cbox_camera_type = new QComboBox(this);
    m_cbox_camera_type->addItem("Dahua");
    m_cbox_camera_type->addItem("Hikvision");
    m_cbox_camera_type->addItem("Other");

    m_btn_save_config = new QPushButton(tr("Save"), this);

    QVBoxLayout *main_hlyt = new QVBoxLayout(this);
    main_hlyt->addWidget(m_gbox_connect_config);
    main_hlyt->addWidget(m_gbox_camera_config);
    main_hlyt->addWidget(m_gbox_picture_config);
    main_hlyt->addWidget(m_btn_save_config);

    QFormLayout *hlyt1 = new QFormLayout(m_gbox_connect_config);
    hlyt1->addRow(tr("CameraNo"), m_cbox_camera_no);
    hlyt1->addRow(tr("ConnectType"), m_cbox_camera_connect_type);
    hlyt1->addRow(tr("CameraIp"), m_ledit_camera_ip);
    hlyt1->addRow(tr("CameraType"), m_cbox_camera_type);

    QFormLayout *hlyt2 = new QFormLayout(m_gbox_camera_config);
    hlyt2->addRow(tr("ExposureTime"), m_ledit_camera_exposure_time);
    hlyt2->addRow(tr("ISO"), m_ledit_camera_ISO);

    QFormLayout *hlyt3 = new QFormLayout(m_gbox_picture_config);
    hlyt3->addRow(tr("TemplatePath"), m_ledit_template_path);
    hlyt3->addRow(tr("OKPath"), m_ledit_ok_path);
    hlyt3->addRow(tr("NGPath"), m_ledit_ng_path);
}
void CameraConfig::initConnect()
{
    connect(m_cbox_camera_no, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CameraConfig::slotCameraNoChanged);
    connect(m_ledit_camera_ip, &QLineEdit::returnPressed, this, [this]() {
        m_config->setIp(m_ledit_camera_ip->text());
        }
    );
    connect(m_ledit_camera_exposure_time, &QLineEdit::returnPressed, this, [this]() {
        m_config->setExposureTime(m_ledit_camera_exposure_time->text().toUInt());
        }
    );
    connect(m_ledit_camera_ISO, &QLineEdit::returnPressed, this, [this]() {
        m_config->setISO(m_ledit_camera_ISO->text().toUInt());
        }
    );
    connect(m_ledit_ng_path, &QLineEdit::returnPressed, this, [this]() {
        m_config->setNGPath(m_ledit_ng_path->text());
        }
    );
    connect(m_ledit_ok_path, &QLineEdit::returnPressed, this, [this]() {
        m_config->setOKPath(m_ledit_ok_path->text());
        }
    );
    connect(m_btn_save_config, &QPushButton::clicked, this, &CameraConfig::slotBtnSaveConfig);
}


void CameraConfig::initModel()
{
    m_config = new Config();
}


void CameraConfig::showEvent(QShowEvent *event)
{
    m_cbox_camera_type->setCurrentText(m_config->getCameraType());
    m_cbox_camera_connect_type->setCurrentIndex(m_config->getConnectType());
    m_cbox_camera_no->setCurrentIndex(m_config->getCameraNo());
    m_ledit_camera_ip->setText(m_config->getIp());

    m_ledit_camera_exposure_time->setText(QString::number(m_config->getExposureTime()));
    m_ledit_camera_ISO->setText(QString::number(m_config->getISO()));

    m_ledit_template_path->setText(m_config->getPictureTemplatePath());
    m_ledit_ok_path->setText(m_config->getOKPath());
    m_ledit_ng_path->setText(m_config->getNGPath());

    QWidget::showEvent(event);
}

void CameraConfig::slotBtnSaveConfig()
{
    m_config->setCameraNo(m_cbox_camera_no->currentIndex());
    m_config->setConnectType(m_cbox_camera_connect_type->currentIndex());
    m_config->setCameraType(m_cbox_camera_type->currentText());
    m_config->saveConfig();
}

void CameraConfig::slotCameraNoChanged(int index)
{
    m_config->setCameraNo(index);
}
