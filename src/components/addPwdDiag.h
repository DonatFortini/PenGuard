#ifndef ADDPWDDIAG_H
#define ADDPWDDIAG_H

#include <gtkmm.h>
#include <gtkmm/dialog.h>
#include <string>

#include "../utilsCache.h"

class addPwdDiag : public Gtk::Dialog
{
public:
    addPwdDiag(std::string wb, std::string usr, std::string pwd);
    ~addPwdDiag();
    using addpwdsig = sigc::signal<void, std::string, std::string, std::string>;
    addpwdsig addpwd_signal();

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
    addpwdsig addpwd;
};

#endif // !ADDPWDDIAG_H