#include "main_window.h"
#include "palette.h"

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent) {
    setGeometry(50, 20, 1000, 800);
    setWindowTitle("Funny Gears");
    setWindowIcon(QIcon("Gear.icns"));
    setUnifiedTitleAndToolBarOnMac(true);

    setPalette(Palette());

    createActions();
    createScene();
    createView();
    createToolbars();
    createMenus(); //Must be executed after createToolbars()
    createLayout();

    projectChanged = true;

    statusBar()->showMessage(tr("Ready"));
};

MainWindow::~MainWindow() {};

QIcon MainWindow::icon() const {
    return windowIcon();
};

void MainWindow::quitProgram() {
    close();
};

void MainWindow::about() {
     QMessageBox::about(this, tr("About Funny Gears"),
            tr("<p><b>Funny Gears</b> wants to demonstrate the challenge of gear construction. </p>"
               "<p><small>Copyright: Katja Renner 2013</small></p>"));
};

void MainWindow::newProject() {
    //TODO: Test if state already saved...
    //TODO: Open new file
};

bool MainWindow::saveProject() {
    return true;
};

bool MainWindow::saveAsProject() {
    return true;
};

void MainWindow::openProject() {
    if((projectChanged && savedProjectOrOk()) || !projectChanged) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a funny gear project"), QString(), tr(".fg"));
        if(!fileName.isEmpty());
            // loadFile(fileName);
    }
};

bool MainWindow::savedProjectOrOk() {
    QMessageBox::StandardButton userRequest;
    userRequest = QMessageBox::warning(this, tr("Save Changes?"),
        tr("<p>You have not saved your project in the current state. Do you want to save it before closing?</p>"
        "<p><small>Your changes will be lost otherwise!</small></p>"),
        (QMessageBox::Cancel | QMessageBox::Discard | QMessageBox::Save),
        QMessageBox::Save);
    if(userRequest == QMessageBox::Save)
        return saveProject();
    else if(userRequest == QMessageBox::Cancel)
        return false;
    else
        return true;
};

void MainWindow::sayHello() {
    std::cout << "MainWindow::sayHello" << std::endl;
};

void MainWindow::createActions() {
    connect(createAction(exitAction,  tr("E&xit"),  tr("quit program"), QKeySequence::Quit),
        SIGNAL(triggered()), this, SLOT(quitProgram()));
    connect(createAction(callAction,  tr("&say hello"),  tr("say hello")),
        SIGNAL(triggered()),  this, SLOT(sayHello()));
    connect(createAction(aboutAction, tr("&About"), tr("about the program")),
        SIGNAL(triggered()), this, SLOT(about()));
    connect(createAction(newAction,   tr("&New"),   tr("create new project"), QKeySequence::New),
        SIGNAL(triggered()), this, SLOT(newProject()));
    connect(createAction(saveAction,  tr("&Save"),  tr("save current objects"), QKeySequence::Save),
        SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(createAction(saveAsAction,tr("Save As"),  tr("save current objects in new file"), QKeySequence::SaveAs),
        SIGNAL(triggered()), this, SLOT(saveAsProject()));
    connect(createAction(openAction,  tr("&Open"),  tr("open saved objects"), QKeySequence::Open),
        SIGNAL(triggered()), this, SLOT(openProject()));
};

QAction* MainWindow::createAction(QAction *&action, QString name, QString statusTip, QKeySequence shortcut) {

    QString iconFileName = QString("images/" + name + ".png");
    QFile iconFile(iconFileName);
    if (iconFile.exists()) {
        action = new QAction(QIcon(iconFileName), name, this);
    } else {
        action = new QAction(name, this);
    }
    action->setStatusTip(statusTip);
    if(shortcut != NULL)
        action->setShortcut(shortcut);
    return action;
};

void MainWindow::createMenus() {
    programMenu = menuBar()->addMenu(tr("Funny Gears"));
    programMenu->addAction(aboutAction);
    programMenu->addSeparator();
    programMenu->addAction(exitAction);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    
    editMenu = menuBar()->addMenu(tr("&Call"));
    editMenu->addAction(callAction);
    editMenu->addAction(aboutAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(toggleFileToolBarAction);
    viewMenu->addAction(toggleEditToolBarAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
};

void MainWindow::createScene() {
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QColor(240, 240, 240));
    scene->update();
};

void MainWindow::createView() {
    view = new QGraphicsView(scene, this);
    view->update();
};

void MainWindow::createToolbars() {
    fileToolBar = this->addToolBar(tr("File"));
    fileToolBar->setIconSize(QSize(16, 16));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);

    editToolBar = this->addToolBar(tr("Edit"));
    editToolBar->addAction(callAction);
    editToolBar->addAction(aboutAction);

    toggleFileToolBarAction = fileToolBar->toggleViewAction();
    toggleEditToolBarAction = editToolBar->toggleViewAction();
};

void MainWindow::createLayout() {

    QPushButton *but = new QPushButton(tr("Mainwidget"));

    objectSchedule = new OptionWidget(tr("Object Schedule"), but, this);
    but = new QPushButton(tr("Blub"));
    objectProperties = new OptionWidget(tr("Object Properties"), but, this);
    but = new QPushButton(tr("Blub"));
    OptionWidget *testWidget = new OptionWidget(tr("Test Options"), but, this);
    but = new QPushButton(tr("Blub"));
    OptionWidget *testWidget2= new OptionWidget(tr("Test 2 Options"), but, this);
    but = new QPushButton(tr("Blub"));
    OptionWidget *testWidget3= new OptionWidget(tr("Test 2 Options"), but, this);

    objectMenu = new OptionListWidget(this);
    objectMenu->add(objectSchedule);
    objectMenu->add(objectProperties);
    objectMenu->add(testWidget);
    objectMenu->add(testWidget2);
    objectMenu->add(testWidget3);
    

    layout = new QHBoxLayout;
    layout->addWidget(view);
    layout->addWidget(objectMenu);

    painting = new QWidget;
    painting->setLayout(layout);
    painting->update();
    setCentralWidget(painting);
};