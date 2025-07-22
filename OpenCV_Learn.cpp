#include "OpenCV_Learn.h"
#include <QFileDialog>

OpenCV::OpenCV()
{
    setWindowTitle("Zhang Graphics Open");
    resize(800, 600);
    initWidget();
    
    connect(btn, SIGNAL(clicked()), this, SLOT(slotBtnClicked()));
}

OpenCV::~OpenCV()
{
}

void OpenCV::initWidget()
{
    QWidget *central_wdt = new QWidget(this);
    glyt = new QGridLayout(central_wdt);
    grv = new QGraphicsView();
    btn = new QPushButton();
    ledit = new QLineEdit();
    scene = new QGraphicsScene();
    grv->setScene(scene);

    glyt->addWidget(grv, 0, 0, 49, 50);
    glyt->addWidget(ledit, 50, 0, 1, 49);
    glyt->addWidget(btn, 50, 49, 1, 1);

    setCentralWidget(central_wdt);
}

void OpenCV::slotBtnClicked()
{
    QFileDialog dlg(this);
    QString path = dlg.getOpenFileName(this, "Open Image", "", "Image Files(*.png *.jpg *.bmp)");


    ledit->setText(path);

    if( !path.isEmpty() )
    {
        QPixmap pix(path);
        scene->addPixmap(pix);
    }
}
