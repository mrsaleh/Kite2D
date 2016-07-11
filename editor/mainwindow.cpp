#include "mainwindow.h"
#include <QtWidgets>
#include <gridscene.h>
#include <expander.h>
#include <vector>
#include <thread>
#include <string>
#include <climits>
#include "frmnewproj.h"
#include "frmprojsettings.h"
#include "comproperty.h"
#include <Kite/serialization/kbinaryserial.h>
#include <Kite/serialization/types/kstdstring.h>
#include <Kite/serialization/types/kstdumap.h>

using namespace Kite;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
	curProject(nullptr),
	kinfo(new KiteInfo),
	exec(new Executer)
{
    this->setMinimumSize(1000, 600);
	setupDocks();
	setupActions();
	setupStatusBar();
    setupToolbar();
	setupMenus();
    setupScene();
	loadDockState();
	disGUI();

	connect(exec, &Executer::started, this, &MainWindow::engineStarted);
	connect(exec, &Executer::paused, this, &MainWindow::enginePaused);
	connect(exec, &Executer::unpaused, this, &MainWindow::engineUnpaused);
	connect(exec, &Executer::stoped, this, &MainWindow::engineStoped);
}

MainWindow::~MainWindow()
{}

void MainWindow::showSwitchOutput() {
	if (outDock->isHidden()) {
		outDock->show();
	} else {
		outDock->hide();
	}
}

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



void MainWindow::setupDocks(){
    // resource dock
	resDock = new ResourceDock(this);
	resDock->setObjectName("Resources");
	resDock->setupCategories(*kinfo->getResourceTypes());
    addDockWidget(Qt::LeftDockWidgetArea, resDock);
	
	// output dock
	outDock = new OutputDock(this);
	addDockWidget(Qt::BottomDockWidgetArea, outDock);
	outDock->hide();

    // objects dock
    objDock = new ObjectDock(this);
    addDockWidget(Qt::LeftDockWidgetArea, objDock);	
	connect(resDock, &ResourceDock::resourceSelected, objDock, &ObjectDock::resEdit);
	connect(resDock, &ResourceDock::resourceDelete, objDock, &ObjectDock::resDelete);
	connect(resDock, &ResourceDock::resourceOpen, objDock, &ObjectDock::installEntityCallback);
	connect(resDock, &ResourceDock::resourceAdded, objDock, &ObjectDock::installEntityCallback);
	connect(objDock, &ObjectDock::requestCreateResource, resDock, &ResourceDock::addResource);
	connect(objDock, &ObjectDock::requestGetResource, resDock, &ResourceDock::getResource);
	connect(objDock, &ObjectDock::requestResName, resDock, &ResourceDock::filterByType);

    // component/properties dock
    prpDock = new ComponentDock(this);
	prpDock->inite(*kinfo->getComponentTypes(), resDock->getDictionary());
    addDockWidget(Qt::RightDockWidgetArea, prpDock);
	connect(objDock, &ObjectDock::objectSelected, prpDock, &ComponentDock::entityEdit);
	connect(objDock, &ObjectDock::objectDelete, prpDock, &ComponentDock::entityDelete);
	connect(prpDock, &ComponentDock::resSelected, resDock, &ResourceDock::selectResource);
	connect(prpDock, &ComponentDock::revertPrefab, objDock, &ObjectDock::revertPrefab);
	connect(prpDock, &ComponentDock::applyPrefab, objDock, &ObjectDock::applyPrefab);

	// kite object browser
	expDock = new QDockWidget(tr("Object Browser"), this);
	expDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, expDock);
	tabifyDockWidget(objDock, expDock);

	auto tview = new QTreeView();
	tview->setModel(kinfo->getModel());
	tview->setHeaderHidden(true);
	expDock->setWidget(tview);
}

void MainWindow::setupScene(){
	mainTab = new MainTab(this);
	mainTab->setCompleterModel(kinfo->getModel());
	connect(resDock, &ResourceDock::resourceSelected, mainTab, &MainTab::selectResource);
	connect(resDock, &ResourceDock::resourceEdit, mainTab, &MainTab::openTabs);
	connect(resDock, &ResourceDock::resourceDelete, mainTab, &MainTab::closeResource);

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
	newProj = new QAction(QIcon(":/icons/new"), "New Project", this);
	newProj->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_N));
	newProj->setShortcutContext(Qt::ApplicationShortcut);
	connect(newProj, &QAction::triggered, this, &MainWindow::newProject);

	openProj = new QAction(QIcon(":/icons/open"), "Open Project", this);
	openProj->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_O));
	openProj->setShortcutContext(Qt::ApplicationShortcut);
	connect(openProj, &QAction::triggered, this, &MainWindow::openProject);

	saveProj = new QAction(QIcon(":/icons/save"), "Save Project", this);
	saveProj->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
	saveProj->setShortcutContext(Qt::ApplicationShortcut);
	connect(saveProj, &QAction::triggered, this, &MainWindow::saveProject);

	closeProj = new QAction("Close Project", this);
	connect(closeProj, &QAction::triggered, this, &MainWindow::closeProject);

	playScene = new QAction(QIcon(":/icons/play"), "Play", this);
	playScene->setShortcut(QKeySequence(Qt::Key_F5));
	playScene->setShortcutContext(Qt::ApplicationShortcut);
	connect(playScene, &QAction::triggered, this, &MainWindow::startEngine);

	pauseScene = new QAction(QIcon(":/icons/pause"), "Pause", this);
	pauseScene->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Pause));
	pauseScene->setShortcutContext(Qt::ApplicationShortcut);
	connect(pauseScene, &QAction::triggered, exec, &Executer::pause);

	stopScene = new QAction(QIcon(":/icons/stop"), "Stop", this);
	stopScene->setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F5));
	stopScene->setShortcutContext(Qt::ApplicationShortcut);
	connect(stopScene, &QAction::triggered, exec, &Executer::stop);

	projSettings = new QAction(QIcon(":/icons/set"), "Project Settings", this);
	projSettings->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F7));
	projSettings->setShortcutContext(Qt::ApplicationShortcut);
	connect(projSettings, &QAction::triggered, this, &MainWindow::openProjSetting);

	showOutputPan = new QAction("Output", this);
	showOutputPan->setShortcut(QKeySequence(Qt::ALT + Qt::Key_2));
	showOutputPan->setShortcutContext(Qt::ApplicationShortcut);
	connect(showOutputPan, &QAction::triggered, this, &MainWindow::showSwitchOutput);

	exit = new QAction(QIcon(":/icons/exit"), "Exit", this);
	exit->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));
	exit->setShortcutContext(Qt::ApplicationShortcut);
	connect(exit, &QAction::triggered, this, &MainWindow::exitApp);
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

	// test
	fileMenu = menuBar()->addMenu(tr("&Test"));
	fileMenu->addAction(playScene);
	fileMenu->addAction(pauseScene);
	fileMenu->addAction(stopScene);

	// window
	winMenu = menuBar()->addMenu(tr("&Window"));

}

void MainWindow::setupToolbar(){
    fileTolb = addToolBar(tr("Toolbar"));
	fileTolb->setObjectName("Toolbar");
	fileTolb->addAction(newProj);
	fileTolb->addAction(openProj);
	fileTolb->addSeparator();
	fileTolb->addAction(saveProj);
	fileTolb->addSeparator();
	fileTolb->addAction(projSettings);
	fileTolb->addSeparator();
	fileTolb->addAction(playScene);
	fileTolb->addAction(pauseScene);
	fileTolb->addAction(stopScene);
}

void MainWindow::setupStatusBar() {
	auto klabel = new QLabel(this);
	klabel->setText("Kite2D ver " + QString::number(K2D_VER_MAJ) +
					"." + QString::number(K2D_VER_MIN) +
					"." + QString::number(K2D_VER_BUILD));
	klabel->setStyleSheet("color: orange;");
	QMainWindow::statusBar()->addPermanentWidget(klabel);

	auto btnShowOutputPan = new QToolButton(this);
	btnShowOutputPan->setDefaultAction(showOutputPan);
	btnShowOutputPan->setToolButtonStyle(Qt::ToolButtonTextOnly);
	QMainWindow::statusBar()->addWidget(btnShowOutputPan);
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
	pauseScene->setDisabled(true);
	stopScene->setDisabled(true);
	saveProj->setDisabled(true);
	closeProj->setDisabled(true);
	playScene->setDisabled(true);
	resDock->setDisabled(true);
	objDock->setDisabled(true);
	prpDock->setDisabled(true);
	projSettings->setDisabled(true);
}

void MainWindow::enGUI() {
	playScene->setDisabled(false);
	saveProj->setDisabled(false);
	closeProj->setDisabled(false);
	playScene->setDisabled(false);
	resDock->setDisabled(false);
	objDock->setDisabled(false);
	prpDock->setDisabled(false);
	projSettings->setDisabled(false);
}

void MainWindow::saveXML(QIODevice *device, const QString &Address){
	QXmlStreamWriter stream(device);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();

	stream.writeStartElement("k2dproject");
	stream.writeAttribute("name", curProject->name);
	stream.writeAttribute("version", "1.0");

	// config
	stream.writeStartElement("config");
	stream.writeStartElement("window");
	stream.writeAttribute("title", curProject->config.window.title.c_str());
	stream.writeAttribute("width", QString::number(curProject->config.window.width));
	stream.writeAttribute("height", QString::number(curProject->config.window.height));
	stream.writeAttribute("xpos", QString::number(curProject->config.window.xpos));
	stream.writeAttribute("ypos", QString::number(curProject->config.window.ypos));
	stream.writeAttribute("startupScene", curProject->config.startUpScene.c_str());
	if (curProject->config.window.fullscreen) {
		stream.writeAttribute("fullscreen", "true");
	} else {
		stream.writeAttribute("fullscreen", "false");
	}
	if (curProject->config.window.showCursor) {
		stream.writeAttribute("showcursor", "true");
	} else {
		stream.writeAttribute("showcursor", "false");
	}
	if (curProject->config.window.resizable) {
		stream.writeAttribute("resizable", "true");
	} else {
		stream.writeAttribute("resizable", "false");
	}
	stream.writeEndElement(); // config.window
	stream.writeEndElement(); // config

	// resources
	stream.writeStartElement("resources");
	auto resDict = resDock->getDictionary();
	for (auto it = resDict->cbegin(); it != resDict->cend(); ++it) {
		KFOStream fstream;
		(*it)->saveStream(&fstream, Address.toStdString() + "/resources/" + it.key().toStdString());
		fstream.close();

		Kite::KBinarySerial bserial;
		bserial << *resDock->getKiteDictionary(Address + "/");
		bserial.saveStream(&fstream, Address.toStdString() + "/dict.kdict", 0);

		stream.writeStartElement("item");
		stream.writeAttribute("name", it.key());
		stream.writeAttribute("type", (*it)->getType().c_str());
		stream.writeEndElement();
	}

	stream.writeEndElement(); // resources

	stream.writeEndElement(); // k2dproject
	stream.writeEndDocument();
}

bool MainWindow::loadXML(QIODevice *device, const QString &Address) {
	QXmlStreamReader xml(device);
	bool head = false;
	bool config = false;
	bool res = false;

	if (xml.readNextStartElement()) {
		if (xml.name() == "k2dproject" && xml.attributes().value("version") == "1.0") {
			QFileInfo finfo(Address);
			curProject->name = xml.attributes().value("name").toString();
			curProject->Path = finfo.path();
			curProject->resPath = finfo.path() + "/resources";
			curProject->config.dictionary = finfo.path().toStdString() + "/dict.kdict";
			head = true;
		}

		while (!xml.atEnd()) {
			xml.readNext();

			// config
			if (xml.isStartElement() && xml.name() == "config") {
				config = true;
				while (!xml.isEndElement()) {
					xml.readNext();

					// window
					if (xml.isStartElement() && xml.name() == "window") {
						curProject->config.window.title = xml.attributes().value("title").toString().toStdString();
						curProject->config.window.width = xml.attributes().value("width").toInt();
						curProject->config.window.height = xml.attributes().value("height").toInt();
						curProject->config.window.xpos = xml.attributes().value("xpos").toInt();
						curProject->config.window.ypos = xml.attributes().value("ypos").toInt();
						curProject->config.startUpScene = xml.attributes().value("startupScene").toString().toStdString();
						if (xml.attributes().value("fullscreen").toString() == "true") {
							curProject->config.window.fullscreen = true;
						} else {
							curProject->config.window.fullscreen = false;
						}

						if (xml.attributes().value("showcursor").toString() == "true") {
							curProject->config.window.showCursor = true;
						} else {
							curProject->config.window.showCursor = false;
						}

						if (xml.attributes().value("resizable").toString() == "true") {
							curProject->config.window.resizable = true;
						} else {
							curProject->config.window.resizable = false;
						}

					}
				}
			}
				
			// resources
			if (xml.isStartElement() && xml.name() == "resources") {
				res = true;
				while (!xml.atEnd()) {
					xml.readNext();
					if (xml.isStartElement() && xml.name() == "item") {
						if (!resDock->openResource(curProject->resPath + "/" + xml.attributes().value("name").toString(),
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
	return (head && res && config);
}

void MainWindow::startEngine() {
	saveProject();
	outDock->getEditor()->clear();
	outDock->autoShow();
	connect(exec, &Executer::engineOutput, this, &MainWindow::getEngineOutput);
	exec->run(&curProject->config);
}

void MainWindow::getEngineOutput(const QString &Text, int MType) {
	switch ((Kite::msgType)MType) {
	case Kite::msgType::MSG_DEBUG:
		outDock->getEditor()->appendHtml("<font color=\"red\"><b>DEBUG: </b></font>" + Text);
		break;
	case Kite::msgType::MSG_BREAK:
		outDock->getEditor()->appendHtml("<font color=\"red\"><b>BREAK: </b></font>" + Text);
		break;
	case Kite::msgType::MSG_ASSERT:
		outDock->getEditor()->appendHtml("<font color=\"red\"><b>ASSERT: </b></font>" + Text);
		break;
	case Kite::msgType::MSG_LUA:
		outDock->getEditor()->appendPlainText("Output: " + Text);
		break;
	default:
		outDock->getEditor()->appendHtml("<font color=\"yellow\"><b>Other: </b></font>" + Text);
		break;
	}
}

void MainWindow::engineStarted() {
	outDock->getEditor()->appendHtml("<font color = \"Aqua\">---- Engine Started ----</font>");
	playScene->setDisabled(true);
	pauseScene->setDisabled(false);
	stopScene->setDisabled(false);
}

void MainWindow::enginePaused() {
	outDock->getEditor()->appendHtml("<font color = \"Aqua\">---- Engine Paused ----</font>");
	playScene->setDisabled(false);
	pauseScene->setDisabled(true);
	stopScene->setDisabled(false);
	disconnect(playScene, &QAction::triggered, 0, 0);
	connect(playScene, &QAction::triggered, exec, &Executer::unpause);
}

void MainWindow::engineUnpaused() {
	outDock->getEditor()->appendHtml("<font color = \"Aqua\">---- Engine Unpaused ----</font>");
	playScene->setDisabled(true);
	pauseScene->setDisabled(false);
	stopScene->setDisabled(false);
	disconnect(playScene, &QAction::triggered, 0, 0);
	connect(playScene, &QAction::triggered, this, &MainWindow::startEngine);
}

void MainWindow::engineStoped() {
	outDock->getEditor()->appendHtml("<font color = \"Aqua\">---- Engine Stoped ----</font>");
	disconnect(exec, &Executer::engineOutput, this, &MainWindow::getEngineOutput);
	outDock->autoHide();
	playScene->setDisabled(false);
	pauseScene->setDisabled(true);
	stopScene->setDisabled(true);
	disconnect(playScene, &QAction::triggered, 0, 0);
	connect(playScene, &QAction::triggered, this, &MainWindow::startEngine);
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
			curProject->config.window.title = curProject->name.toStdString();
			curProject->config.window.width = 800;
			curProject->config.window.height = 600;
			curProject->config.window.xpos = 100;
			curProject->config.window.ypos = 100;
			curProject->config.window.fullscreen = false;
			curProject->config.window.showCursor = true;
			curProject->config.window.resizable = false;
			curProject->config.dictionary = curProject->Path.toStdString() + "/dict.kdict";

			this->setWindowTitle("Kite2D Editor - " + frm.getName());
			resDock->setCurrentDirectory(curProject->resPath);

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
				curProject = new Project;
				if (loadXML(&file, fileName)) {
					resDock->setCurrentDirectory(curProject->resPath);
					enGUI();
				} else {
					delete curProject;
					curProject = nullptr;
				}
				file.close();
			}
		}
	}
}

void MainWindow::saveProject() {
	if (curProject != nullptr) {
		resDock->manageUsedResource(kinfo->getResourceComponentsTypes());
		mainTab->saveAll();
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
		resDock->clearResources();
		resDock->setupCategories(*kinfo->getResourceTypes());

		delete curProject;
		curProject = nullptr;

		disGUI();
	}
}

void MainWindow::openProjSetting() {
	QStringList list;
	resDock->filterByType("KScene", list);
	list.push_front("<default>"); // default scene
	frmProjSettings frm(this, &curProject->config, list);
	frm.exec();
}
