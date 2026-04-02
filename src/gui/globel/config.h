#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QSettings>

class Config
{
public:
    Config();
    ~Config();
    void loadConfig();
    void saveConfig();

    void setCameraCount(int count);
    int getCameraCount();

    void setIp(QString text);
    QString getIp();
    void setConnectType(int index);
    int getConnectType();
    void setCameraType(QString name);
    QString getCameraType();

    void setCameraNo(int no);
    int getCameraNo();
    void setExposureTime(int time);
    int getExposureTime();
    void setISO(int iso);
    int getISO();

    void setPictureTemplatePath(const QString &path);
    QString getPictureTemplatePath();
    void setOKPath(const QString &path);
    QString getOKPath();
    void setNGPath(const QString &path);
    QString getNGPath();

private:
    bool m_is_saved;
    const QString m_config_file_path;
    QSettings m_settings;

    int m_camera_count;

    QString m_ip;
    int m_connect_type;
    QString m_camera_type;

    int m_camera_no;
    QString m_picture_template_path;
    QString m_ok_path;
    QString m_ng_path;
    int m_exposure_time;
    int m_iso;

};

#endif // !
