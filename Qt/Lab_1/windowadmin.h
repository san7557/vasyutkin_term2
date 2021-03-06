#ifndef WINDOWADMIN_H
#define WINDOWADMIN_H

#include <QDialog>
#include "database.h"
#include "person.h"
#include "departurejournal.h"
#include "changepass.h"
#include "wiewjournaluser.h"
#include <QMessageBox>
#include "newauto.h"

namespace Ui {
class WindowAdmin;
}

class WindowAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit WindowAdmin(QWidget *parent = nullptr);
    ~WindowAdmin();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::WindowAdmin *ui;
    DepartureJournal *journol;
    WiewJournalUser *jaurnol;
    ChangePass *windoww;
    vector <ffile> *user;
    NewAuto *newcar;
};

#endif // WINDOWADMIN_H
