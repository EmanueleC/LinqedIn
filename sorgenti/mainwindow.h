#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "homewindow.h"
#include "homeadmin.h"
#include "controller.h"


class mainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Controller* controller; // è compito della MainWindow eliminare il controller alla fine
    HomeWindow* home; // home di Linqedin per utente
    HomeAdmin* homeAdmin; // finestra per l'amministratore

    // menù in comune

    QMenu *fileMenu, *helpMenu;
    QAction *exitAct, *aboutAct, *fullAct;
    Rettangolo* rett;

    void createActions();
    void createMenus();

private slots:
    void about();
public:
    mainWindow();
};

#endif // MAINWINDOW_H
