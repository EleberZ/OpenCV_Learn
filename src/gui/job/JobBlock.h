#ifndef JOB_BLOCK_H
#define JOB_BLOCK_H

#include <QWidget>

class JobBlock
{
	Q_OBJECT
public:
	JobBlock(QWidget *parent = nullptr);
	~JobBlock();
	void initWidget();
private:

};

#endif // JOB_BLOCK_H