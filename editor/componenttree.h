#ifndef COMPONENTTREE_H
#define COMPONENTTREE_H

#include <qtreewidget.h>
#include <qstringlist.h>
#include <qaction.h>
#include <Kite/core/kentity.h>
#include <Kite/core/kcomponent.h>
#include <Kite/meta/kmetamanager.h>
#include <Kite/meta/kmetabase.h>
#include <Kite/meta/kmetaclass.h>
#include <Kite/meta/kmetapod.h>

class QMenu;
class QFormLayout;

enum ComActState {
	CA_ON_LOAD,
	CA_ON_ITEM,
	CA_ON_INITE
};

class ComponentTree : public QTreeWidget {
	Q_OBJECT

public:
	explicit ComponentTree(QWidget *parent = 0);
	~ComponentTree();

	void setupTypes(const QStringList &TypeList);
	inline QFrame *getHeaderTools() { return htools; }

public slots:
	void entityEdit(Kite::KEntity *Entity);
	void entityDelete(Kite::KEntity *Entity);

signals:
	void componentAdded(Kite::KEntity *Entity, Kite::KComponent *Com);
	void componentDelete(Kite::KEntity *Entity, Kite::KComponent *Com);
	void componentEdited(Kite::KEntity *Entity, Kite::KComponent *Com);

private slots:
	void actRClicked(const QPoint & pos);
	void actAdd(QAction *Action);
	void actAddDef();
	void actRemove();
	void actEdit();
	void actClear();
	void actSearch(const QString &Pharase);

protected:
	void focusInEvent(QFocusEvent *Event) override;
	void focusOutEvent(QFocusEvent *Event) override;

private:
	void setupActions();
	void setupShortcuts();
	void setupHTools();
	void actionsControl(ComActState State);
	QString getAvailName(Kite::KEntity *Entity);
	void removeComponentGUI();
	void createComponent(const Kite::KEntity *Entity, const Kite::KComponent *Component);
	void bindProperties(const Kite::KEntity *Entity, const Kite::KComponent *Component, QFrame *Frame);
	void addGUIItem(QFormLayout *Layout, const Kite::KMetaBase *Meta, const Kite::KEntity *Entity,
					const Kite::KComponent *Component, const Kite::KMetaProperty *PropMeta);

	QAction *addDefComp;
	QAction *remComp;
	QFrame *htools;
	QLineEdit *ledit;
	QVector<QShortcut *> shortcuts;
	QMenu *mtypes;
	Kite::KEntity *currEntity;
	QStringList types;
	Kite::KMetaManager mman;
};

#endif // COMPONENTTREE_H
