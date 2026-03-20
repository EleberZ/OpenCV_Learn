#ifndef ZDOCKWIDGET_H
#define ZDOCKWIDGET_H

#include <QDockWidget>
#include <QLabel>
#include <QToolButton>


class ZDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit ZDockWidget(const QString &title, QWidget *parent = nullptr);
    ~ZDockWidget();
    void setWidget(QWidget *widget);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private slots:
    void slotToggleCollapse();
private:
    QLabel *m_lab_title;
    QToolButton *m_btn_close;
    QToolButton *m_btn_minimize;
    bool m_bCollapse;
    QWidget *m_contentWdt;

};
#endif // ZDOCKWIDGET_H
