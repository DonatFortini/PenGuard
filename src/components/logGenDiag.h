#ifndef LOGGENDIAG_H
#define LOGGENDIAG_H
#include <gtkmm.h>
#include <gtkmm/dialog.h>
#include <string>

#include "../client.h"
#include "../utilsCache.h"

class logGenDiag : public Gtk::Dialog
{
public:
    logGenDiag(std::string user_id_string);
    logGenDiag();
    ~logGenDiag();
    std::string user_id;
    void generate_password(void);

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
};

#endif // !LOGGENDIAG_H