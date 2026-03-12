#ifndef JOB_BLOCK_H
#define JOB_BLOCK_H

#include <QWidget>

class JobBlock: public QWidget
{
	Q_OBJECT
public:
	JobBlock(QWidget *parent = nullptr);
	void initWidget();
private:

};

#endif // JOB_BLOCK_H