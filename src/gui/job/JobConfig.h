#ifndef JOB_CONFIG_H
#define JOB_CONFIG_H

#include "JobEditViewImp.h"
#include<QTreeWidgetItem>
#include<QWidget>
#include<QComboBox>
#include<QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "JobEditModel.h"

class JobConfig : public JobEditViewImp
{
    Q_OBJECT
public:
    explicit JobConfig(QWidget *parent = nullptr);
    // 通过 JobEditViewImp 继承
    void initWidget()override;
    void updateWidget()override;
    void updateWidget(BlockData block);
    void initConnect();
    bool setMainGroubBoxTitle(const QString &title);
signals:
    void sglBtnSave();
public slots:
    void slotNotifyJobEditView()override;
    void slotJobBlockDoubleClicked(QTreeWidgetItem *item);
    void slotCheckEnableMask(bool ischeck);
private:
    QString m_job_block_name;
    QGroupBox *m_gbox_main;
    QGroupBox *m_gbox_path;
    QGroupBox *m_gbox_picture_show;

    QComboBox *m_cbox_job_mode;
    QComboBox *m_template_match_method;

    QPushButton *m_btn_save;

    QCheckBox *m_check_enable_mask;

    QLabel *m_label_template_file;
    QLabel *m_label_mask_file;

    QLineEdit *m_ledit_template_file;
    QLineEdit *m_ledit_mask_file;
    QLineEdit *m_ledit_roi_width;
    QLineEdit *m_ledit_roi_height;
    QLineEdit *m_ledit_roi_x;
    QLineEdit *m_ledit_roi_y;

    QGraphicsView *m_graphic_view_template;
    QGraphicsView *m_graphic_view_mask;

    QGraphicsScene *m_graphic_scene_template;
    QGraphicsScene *m_graphic_scene_mask;
};

#endif
