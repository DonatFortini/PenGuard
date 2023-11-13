#ifndef GTKMM_MANAGER_H
#define GTKMM_MANAGER_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm.h>

#include <string.h>
#include "../db/db.h"

class Manager : public Gtk::Window
{
public:
    Manager(void);
    ~Manager();
    void on_validate_clicked();
    bool isNotEmpty();
    void show_alert(const std::string &message);

protected:
    Gtk::Box mainBox;
    Gtk::Box fieldBox;
    Gtk::Entry mdp;
    Gtk::Entry login;
    Gtk::Button validate;
    Gtk::Box logoBox;
    Gtk::Image logo;
};

#endif // GTKMM_MANAGER_H