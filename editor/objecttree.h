#ifndef OBJECTTREE_H
#define OBJECTTREE_H

#include <qtreewidget.h>
#include <qstringlist.h>
#include <qaction.h>
#include <Kite/core/kscene.h>
#include <Kite/core/kentity.h>
#include <Kite/core/kentitymanager.h>

enum ObjectActState {
	OA_ON_LOAD,
	OA_ON_ITEM,
	OA_ON_INITE
};

class ObjectTree : public QTreeWidget {
	Q_OBJECT

public:
	explicit ObjectTree(QWidget *parent = 0);
	~ObjectTree();

	inline QFrame *getHeaderTools() { return htools; }

public slots:
	void sceneEdit(Kite::KResource *Scene);
	void sceneDelete(Kite::KResource *Scene);

signals:
	void objectAdded(Kite::KEntity *Obj);
	void objectSelected(Kite::KEntity *Obj);
	void objectDelete(Kite::KEntity *Obj);
	void objectRenamed(Kite::KEntity *RObjes);

private slots:
	void entityChecked(QTreeWidgetItem *Item, int Col);
	void actClicked();
	void actRClicked(const QPoint & pos);
	void actAddChild();
	void actAddRoot();
	void actRemove();
	void actRename();
	void actSearch(const QString &Pharase);

protected:
	void focusInEvent(QFocusEvent *Event) override;
	void focusOutEvent(QFocusEvent *Event) override;

private:
	void setupActions();
	void setupShortcuts();
	void setupHTools();
	void actionsControl(ObjectActState State);
	void loadChilds(Kite::KEntityManager *Eman, const Kite::KHandle &Entity, QTreeWidgetItem *Parrent);
	QString getAvailName();

	QAction *addRootObj;
	QAction *addChildObj;
	QAction *renameObj;
	QAction *remObj;
	QFrame *htools;
	QLineEdit *ledit;
	QVector<QShortcut *> shortcuts;
	Kite::KScene *currScene;
};

#endif // OBJECTTREE_H
