#ifndef CAMER_CONFIG_H
#define CAMER_CONFIG_H

#include"config.h"
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>

class CameraConfig:public QWidget
{
    Q_OBJECT
public:
    CameraConfig(QWidget *parent = nullptr);
    void initWidget();
    void initConnect();
    void initModel();
    //~CamerConfig();
protected:
    void showEvent(QShowEvent *event) override;
private slots:
    void slotCameraNoChanged(int index);
    void slotBtnSaveConfig();
public:
    QLineEdit *m_ledit_camera_ip;
    QLineEdit *m_ledit_camera_exposure_time;
    QLineEdit *m_ledit_camera_ISO;
    QLineEdit *m_ledit_template_path;
    QLineEdit *m_ledit_ng_path;
    QLineEdit *m_ledit_ok_path;

    QComboBox *m_cbox_camera_connect_type;
    QComboBox *m_cbox_camera_no;
    QComboBox *m_cbox_camera_type;

    QGroupBox *m_gbox_connect_config;
    QGroupBox *m_gbox_camera_config;
    QGroupBox *m_gbox_picture_config;

    QPushButton *m_btn_save_config;

    Config *m_config;
};

#endif // CAMER_CONFIG_H
