#ifndef ADDPWDDIAG_H
#define ADDPWDDIAG_H

#include <gtkmm.h>
#include <gtkmm/dialog.h>
#include <string>

#include "../client.h"
#include "../utilsCache.h"


class addPwdDiag : public Gtk::Dialog
{
public:
    addPwdDiag();
    addPwdDiag(std::string wb, std::string usr, std::string pwd);
    ~addPwdDiag();
protected:
    Gtk::Label wbLabel = Gtk::Label("Website:");
    Gtk::Entry wbEntry;
    Gtk::Label usrLabel = Gtk::Label("Username:");
    Gtk::Entry usrEntry;
    Gtk::Label pwdLabel = Gtk::Label("Password:");
    Gtk::Entry pwdEntry;
    Gtk::Box fieldBox;
    Gtk::Box buttonBox;
    Gtk::Button add = Gtk::Button("Add");
    Gtk::Button cancel = Gtk::Button("Cancel");
    std::vector<Gtk::Widget *> widgets = {&wbLabel, &wbEntry, &usrLabel, &usrEntry, &pwdLabel, &pwdEntry};
};

#endif // !ADDPWDDIAG_H