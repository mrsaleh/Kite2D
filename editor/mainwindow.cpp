#include "mainwindow.h"
#include <QtWidgets>
#include <gridscene.h>
#include <expander.h>
#include <vector>
#include <thread>
#include <string>
#include <climits>
#include "frmnewproj.h"
#include "comproperty.h"

#include <Kite/meta/kmetamanager.h>
#include <Kite/core/kresourcemanager.h>
#include <kmeta.khgen.h>

using namespace Kite;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
	curProject(nullptr)
{
    this->setMinimumSize(1000, 600);
	setupStatusBar();
	scanKiteMeta();
	setupActions();
    setupToolbar();
	setupMenus();
    setupDocks();
    setupScene();
	loadDockState();
	disGUI();
}

MainWindow::~MainWindow()
{}

void MainWindow::closeEvent(QCloseEvent *event) {
	//! Ignore the event by default.. otherwise the window will be closed always.
	event->ignore();

	closeProject();
	if (curProject != nullptr) {
		return;
	}

	saveDockState();
	event->accept();
}

void MainWindow::exitApp() {
	closeProject();
	if (curProject == nullptr) {
		this->close();
	}
}

void MainWindow::selectTabs(Kite::KResource *Res) {
	auto found = resTabs.find(Res->getResourceName().c_str());

	if (found == resTabs.end()) {
		if (Res->getResourceType() == "KScene") {
			mainTab->setTabText(0, Res->getResourceName().c_str());
			mainTab->setCurrentIndex(0);
		}

	} else {
		if (Res->getResourceType() == "KScript") {
			mainTab->setCurrentIndex((*found));
		}
	}
}

void MainWindow::openTabs(Kite::KResource *Res) {
	auto found = resTabs.find(Res->getResourceName().c_str());

	if (found == resTabs.end()) {
		if (Res->getResourceType() == "KScript") {
			auto tb = new QToolButton();
			tb->setFixedSize(15, 15);
			auto tid = mainTab->addTab(new CodeEditor(), Res->getResourceName().c_str());
			mainTab->tabBar()->setTabButton(tid, QTabBar::ButtonPosition::RightSide, tb);
			mainTab->setCurrentIndex(tid);
			resTabs.insert(Res->getResourceName().c_str(), tid);
		}

		if (Res->getResourceType() == "KScene") {
			mainTab->setTabText(0, Res->getResourceName().c_str());
			mainTab->setCurrentIndex(0);
		}

	} else {
		if (Res->getResourceType() == "KScript") {
			mainTab->setCurrentIndex((*found));
		}
	}
}

void MainWindow::closeTabs(Kite::KResource *Res) {

}

void MainWindow::clearTabs() {

}

void MainWindow::setupDocks(){
	QMainWindow::statusBar()->showMessage("Initializing GUI (Docks) ...");

    // resource dock
    resDock = new QDockWidget(tr("Resource Explorer"), this);
	resDock->setObjectName("Resources");
    resDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    resDock->setMinimumWidth(120);
    addDockWidget(Qt::LeftDockWidgetArea, resDock);

	resTree = new ResourceTree(this);
	resTree->setupCategories(kresCatList);
	resDock->setWidget(resTree);
	resDock->setTitleBarWidget(resTree->getHeaderTools());

    // objects dock
    objDock = new QDockWidget(tr("Hierarchy"), this);
	objDock->setObjectName("Hierarchy");
    objDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    objDock->setMinimumWidth(120);
    addDockWidget(Qt::LeftDockWidgetArea, objDock);

	objTree = new ObjectTree(this);
	objDock->setWidget(objTree);
	objDock->setTitleBarWidget(objTree->getHeaderTools());

	connect(resTree, &ResourceTree::resourceSelected, objTree, &ObjectTree::sceneEdit);
	connect(resTree, &ResourceTree::resourceDelete, objTree, &ObjectTree::sceneDelete);

    // component/properties dock
    prpDock = new QDockWidget(tr("Components Editor"), this);
	prpDock->setObjectName("Components Editor");
    prpDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    prpDock->setMinimumWidth(120);
    addDockWidget(Qt::RightDockWidgetArea, prpDock);

	propTree = new ComponentTree;
	propTree->setupTypes(kcompList);
	propTree->setResDictionary(resTree->getDictionary());
	prpDock->setWidget(propTree);
	prpDock->setTitleBarWidget(propTree->getHeaderTools());

	connect(objTree, &ObjectTree::objectSelected, propTree, &ComponentTree::entityEdit);
	connect(objTree, &ObjectTree::objectDelete, propTree, &ComponentTree::entityDelete);

	// code editor
	connect(resTree, &ResourceTree::resourceSelected, this, &MainWindow::selectTabs);
	connect(resTree, &ResourceTree::resourceEdit, this, &MainWindow::openTabs);
	connect(resTree, &ResourceTree::resourceDelete, this, &MainWindow::closeTabs);

	QMainWindow::statusBar()->showMessage("Ready");
}

void MainWindow::setupScene(){
	mainTab = new QTabWidget(this);
	mainTab->setStyleSheet("QTabBar::tab { height: 23px; }");
	mainTab->setMovable(true);

    sceneView = new QGraphicsView();
	mainTab->addTab(sceneView, "Scene");

	setCentralWidget(mainTab);
	
	GridScene *scene1 = new GridScene(25, 20, 32, 32);
	QPixmap plogo("F:\\MyImage\\Kite\\Logo-2-tr.png");
	QGraphicsPixmapItem *logo = new QGraphicsPixmapItem(plogo);
	logo->setPos((scene1->width() / 2) - (plogo.width() / 2), (scene1->height() / 2) - (plogo.height() / 2));
	scene1->addItem(logo);
	sceneView->setScene(scene1);
}

void MainWindow::setupActions() {
	QMainWindow::statusBar()->showMessage("setup actions ...");

	newProj = new QAction(QIcon(":/icons/new"), "New Project", this);
	connect(newProj, &QAction::triggered, this, &MainWindow::newProject);

	openProj = new QAction(QIcon(":/icons/open"), "Open Project", this);
	connect(openProj, &QAction::triggered, this, &MainWindow::openProject);

	saveProj = new QAction(QIcon(":/icons/save"), "Save Project", this);
	connect(saveProj, &QAction::triggered, this, &MainWindow::saveProject);

	closeProj = new QAction("Close Project", this);
	connect(closeProj, &QAction::triggered, this, &MainWindow::closeProject);

	playScene = new QAction(QIcon(":/icons/play"), "Play", this);

	exit = new QAction(QIcon(":/icons/exit"), "Exit", this);
	connect(exit, &QAction::triggered, this, &MainWindow::exitApp);

	QMainWindow::statusBar()->showMessage("Ready");
}

void MainWindow::setupMenus(){
	// menu bar
	menuBar()->setStyleSheet("QMenu::separator {\n"
							 "height: 1px;\n"
							 "background: rgb(129, 129, 129);\n"
							 "margin-left: 25px;}");

	// file
    fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newProj);
	fileMenu->addAction(openProj);
	fileMenu->addSeparator();
	fileMenu->addAction(closeProj);
	fileMenu->addSeparator();
	fileMenu->addAction(saveProj);
	fileMenu->addSeparator();
	fileMenu->addAction(exit);

	// window
	winMenu = menuBar()->addMenu(tr("&Window"));

}

void MainWindow::run() {

}

void MainWindow::setupToolbar(){
    fileTolb = addToolBar(tr("Toolbar"));
	fileTolb->setObjectName("Toolbar");
	fileTolb->addAction(newProj);
	fileTolb->addAction(openProj);
	fileTolb->addSeparator();
	fileTolb->addAction(saveProj);
	fileTolb->addSeparator();
	fileTolb->addAction(playScene);
}

void MainWindow::setupStatusBar() {
	QMainWindow::statusBar()->showMessage("Ready");
}

void MainWindow::loadDockState() {
	QSettings settings;
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("state").toByteArray());
}

void MainWindow::saveDockState() {
	QSettings settings;
	settings.setValue("geometry", saveGeometry());
	settings.setValue("state", saveState());
}

void MainWindow::disGUI() {
	playScene->setDisabled(true);
	saveProj->setDisabled(true);
	closeProj->setDisabled(true);
	playScene->setDisabled(true);
	resDock->setDisabled(true);
	objDock->setDisabled(true);
	prpDock->setDisabled(true);
}

void MainWindow::enGUI() {
	playScene->setDisabled(false);
	saveProj->setDisabled(false);
	closeProj->setDisabled(false);
	playScene->setDisabled(false);
	resDock->setDisabled(false);
	objDock->setDisabled(false);
	prpDock->setDisabled(false);
}

void MainWindow::saveXML(QIODevice *device, const QString &Address){
	QXmlStreamWriter stream(device);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();

	stream.writeStartElement("k2dproject");
	stream.writeAttribute("name", curProject->name);
	stream.writeAttribute("version", "1.0");

	stream.writeStartElement("resources");
	auto resDict = resTree->getDictionary();
	for (auto it = resDict->cbegin(); it != resDict->cend(); ++it) {
		KFOStream fstream;
		fstream.open(Address.toStdString() + "/resources/" + it.key().toStdString() + ".kres", Kite::KIOTypes::KRT_BIN);
		(*it)->saveStream(&fstream);
		fstream.close();
		stream.writeStartElement("item");
		stream.writeAttribute("name", it.key());
		stream.writeAttribute("type", (*it)->getResourceType().c_str());
		stream.writeEndElement();
	}

	stream.writeEndElement(); // resources
	stream.writeEndElement(); // k2dproject
	stream.writeEndDocument();
}

bool MainWindow::loadXML(QIODevice *device, const QString &Address) {
	QXmlStreamReader xml(device);
	bool head = false;
	bool res = false;

	if (xml.readNextStartElement()) {
		if (xml.name() == "k2dproject" && xml.attributes().value("version") == "1.0") {
			QFileInfo finfo(Address);
			curProject = new Project;
			curProject->name = xml.attributes().value("name").toString();
			curProject->Path = finfo.path();
			curProject->resPath = finfo.path() + "/resources";
			head = true;
		}

		while (!xml.atEnd()) {
			xml.readNext();
			if (xml.isStartElement() && xml.name() == "resources") {
				res = true;
				while (!xml.atEnd()) {
					xml.readNext();
					if (xml.isStartElement() && xml.name() == "item") {
						if (!resTree->openResource(curProject->resPath + "/" + xml.attributes().value("name").toString() + ".kres",
												  xml.attributes().value("type").toString())) {
							return false;
						}
					}
				}
			}
		}
	}



	if (xml.hasError()) {
		QMessageBox msg;
		msg.setWindowTitle("Message");
		msg.setText("cant load project file.\nfile address: " + Address 
					+ "\nXML Error: " + xml.errorString());
		msg.exec();
		return false;
	}
	return (head && res);
}

void MainWindow::scanKiteMeta() {
	QMainWindow::statusBar()->showMessage("Scaning Kite2D ...");

	// register kiet meta system
	Kite::KMetaManager kmman;
	Kite::registerKiteMeta(&kmman);

	// dump all mete information
	std::vector<const KMetaBase *> meta;
	kmman.dump(meta);

	// searching for resource categories
	kresCatList.clear();
	kcompList.clear();
	for (auto it = meta.begin(); it != meta.end(); ++it) {
		if (((*it)->getFlag() & RESOURCE) && !((*it)->getFlag() & ABSTRACT)) {
			kresCatList.push_back((*it)->getName().c_str());
			continue;
		}

		if (((*it)->getFlag() & COMPONENT) && !((*it)->getFlag() & ABSTRACT)) {
			auto infoList = (*it)->getInfo();
			for (auto ilit = infoList->begin(); ilit != infoList->end(); ++ilit) {
				if (ilit->first == "KI_CTYPE") {
					kcompList.push_back(ilit->second.c_str());
				}
			}
			continue;
		}

	}

	QMainWindow::statusBar()->showMessage("Ready");
}

void MainWindow::newProject() {

	// close current project if any
	closeProject();

	if (curProject == nullptr) {
		frmNewProj frm(this);
		frm.exec();

		if (frm.isOk()) {
			curProject = new Project;
			curProject->name = frm.getName();
			curProject->Path = frm.getPath() + "/" + curProject->name;
			curProject->resPath = curProject->Path  + "/resources";

			this->setWindowTitle("Kite2D Editor - " + frm.getName());

			enGUI();
		}
	}
}

void MainWindow::openProject() {
	// close current project if any
	closeProject();

	if (curProject == nullptr) {
		QString fileName = QFileDialog::getOpenFileName(this,
												"Open Project", "", "Kite2D Project File (*.k2d)");

		if (!fileName.isEmpty()) {
			QFile file(fileName);
			if (file.open(QIODevice::ReadOnly)) {
				if (loadXML(&file, fileName)) {
					enGUI();
				}
				file.close();
			}
		}
	}
}

void MainWindow::saveProject() {
	if (curProject != nullptr) {
		QFile file(curProject->Path + "/" + curProject->name + ".k2d");
		if (file.open(QIODevice::WriteOnly)) {
			saveXML(&file, curProject->Path);
			file.close();
		}
	}
}

void MainWindow::closeProject() {
	if (curProject != nullptr) {
		int ret = QMessageBox::warning(this, "Kite2D Editor",
									   "Do you want to save changes to " + curProject->name + "?",
									   QMessageBox::Save | QMessageBox::Discard
									   | QMessageBox::Cancel,
									   QMessageBox::Save);

		if (ret == QMessageBox::Save) {
			saveProject();
		} else if (ret == QMessageBox::Cancel) {
			return;
		}

		this->setWindowTitle("Kite2D Editor");

		// clear resource tree
		resTree->clearResources();
		resTree->setupCategories(kresCatList);

		delete curProject;
		curProject = nullptr;

		disGUI();
	}
}
