#ifndef GTKMM_MANAGER_H
#define GTKMM_MANAGER_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm.h>

#include "../db/db.h"
#include "utilsCache.h"

class Manager : public Gtk::Window
{
public:
    Manager(void);
    ~Manager();
    void on_validate_clicked(void);
    bool is_not_empty(void);
    // signal accessors:
    using send = sigc::signal<void, std::string>;
    send logged_signal();

protected:
    Gtk::Box mainBox;
    Gtk::Box fieldBox;
    Gtk::Entry mdp;
    Gtk::Entry login;
    Gtk::Button validate;
    Gtk::Box logoBox;
    Gtk::Image logo;
    send logged;
};

#endif // GTKMM_MANAGER_H