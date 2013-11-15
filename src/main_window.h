#ifndef MAINWINDOW
#define MAINWINDOW

#include "stable.h"
#include "option_widget.h" //TODO: move to stable as soon as stable
#include "option_list_widget.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow();

    QIcon icon() const;

private slots:
    void quitProgram();
    void about();
    void newProject();
    bool saveProject();
    bool saveAsProject();
    void openProject();
    void sayHello();

private:

    QMenu   *programMenu,
            *fileMenu,
            *editMenu,
            *viewMenu,
            *helpMenu;
    QToolBar *fileToolBar,
            *editToolBar;
    QAction *exitAction,
            *newAction,
            *saveAction,
            *saveAsAction,
            *openAction,
            *aboutAction,
            *callAction,
            *toggleFileToolBarAction,
            *toggleEditToolBarAction;
    OptionWidget
            *objectSchedule,
            *objectProperties;
    OptionListWidget
            *objectMenu;

    QWidget *painting;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QHBoxLayout *layout;

    bool projectChanged;
    
    void createActions();
    QAction* createAction(QAction *&action, QString name, QString statusTip, QKeySequence shortcut = NULL);
    void createMenus();
    void createScene();
    void createView();
    void createToolbars();
    void createLayout();
    bool savedProjectOrOk();

};

#endif //MAINWINDOW