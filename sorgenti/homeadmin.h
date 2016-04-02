#ifndef HOMEADMIN_H
#define HOMEADMIN_H
#include "adminwindow.h"
#include "rettangolo.h"


class HomeAdmin: public QWidget
{
    Q_OBJECT
private:
    Controller* controller;
    Rettangolo* rettangolo;
    AdminWindow* adminWindow;
    QGroupBox* homeBox;
    QPushButton* accesso, * logOut;
    QLineEdit* admin, *password;
    QVBoxLayout* homeLayout;
    QLabel* infoLinqedIn;
public:
    HomeAdmin(Controller *);
    void CaricaHomeAdmin();
public slots:
    void accedi();
    void esci();
};

#endif // HOMEADMIN_H
