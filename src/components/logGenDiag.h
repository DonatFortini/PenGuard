#ifndef LOGGENDIAG_H
#define LOGGENDIAG_H
#include <gtkmm.h>
#include <gtkmm/dialog.h>
#include <string>
#include <iostream>

#include "../utilsCache.h"

class logGenDiag : public Gtk::Dialog
{
public:
    logGenDiag(std::string user_id_string);
    ~logGenDiag();
    std::string user_id;
    void generate_password(void);
    using send = sigc::signal<void, std::string, std::string, std::string>;
    send loggen_signal();

protected:
    Gtk::Box mainBox;
    Gtk::Box fieldBox;
    Gtk::Label username = Gtk::Label("Username:");
    Gtk::Entry usrEntry;
    Gtk::Label password = Gtk::Label("Password:");
    Gtk::Entry pwdEntry;
    Gtk::Widget *widgets[4] = {&username, &usrEntry, &password, &pwdEntry};
    Gtk::Box buttons;
    Gtk::Button generate = Gtk::Button("Generate");
    Gtk::Button create = Gtk::Button("Create");
    send loggen;
};

#endif // !LOGGENDIAG_H