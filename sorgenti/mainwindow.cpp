#include "mainwindow.h"
#include <QTabWidget>

mainWindow::mainWindow() :
    controller(new Controller)
{
        home = new HomeWindow(controller);
        homeAdmin = new HomeAdmin(controller);
        QSplitter * splitter = new QSplitter;
        createActions();
        createMenus();
        splitter->addWidget(home);
        splitter->addWidget(homeAdmin);
        splitter->setChildrenCollapsible(false); // impedisce allo splitter di collassare
        setCentralWidget(splitter);
        setWindowTitle(tr("Linqedin"));
        showMaximized();
}

void mainWindow::createActions()
{
    aboutAct = new QAction(tr("About LinQedIn"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    exitAct = new QAction(tr("Esci da LinQedIn"), this);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    fullAct = new QAction(tr("Schermo intero"), this);
    connect(fullAct, SIGNAL(triggered()), this, SLOT(showFullScreen()));
}

void mainWindow::createMenus()
{
    helpMenu = menuBar()->addMenu(tr("Info"));
    helpMenu->addAction(aboutAct);
    helpMenu = menuBar()->addMenu(tr("Vista"));
    helpMenu->addAction(fullAct);
    fileMenu = menuBar()->addMenu(tr("Esci"));
    fileMenu->addAction(exitAct);
}

void mainWindow::about()
{
    QMessageBox::about(this, tr("Informazioni su Linqedin"),
        tr("<b> Linqedin </b> è un sistema che gestisce un piccolo database di utenti"));
}
