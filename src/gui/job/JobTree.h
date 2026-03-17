#ifndef JOB_TREE_H
#define JOB_TREE_H

#include <QTreeWidget>
#include <QWidget>

<<<<<<< HEAD
class JobTree: public QWidget
=======
class JobTree
>>>>>>> cede7bf335a31cce20ae890e04d723e12abc47e0
{
	Q_OBJECT
public:
	JobTree(QWidget *parent = nullptr);
<<<<<<< HEAD
=======
	~JobTree();
>>>>>>> cede7bf335a31cce20ae890e04d723e12abc47e0
	void initWidget();
private:
	QTreeWidget *treeWidget;
};


#endif // JOB_TREE_H