#ifndef GTKMM_CLIENT_H
#define GTKMM_CLIENT_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm.h>

#include "../db/db.h"

class Client : public Gtk::Window
{
public:
    Client(std::string login);
    ~Client();
    void add_password(void);
    void edit_field(Gtk::Entry &username, Gtk::Entry &password, Gtk::Entry &website);
    void disconnect_user(void);
    void generate_logs(void);
    std::string generate_password(void);

protected:
    Gdk::RGBA backgroundColor;
    Gdk::RGBA backgroundColor2;
    Gdk::RGBA buttonColor;
    Gdk::RGBA textColor;
    std::string logged_user;
    Gtk::Box mainBox;
    Gtk::Box leftBox;
    Gtk::Box rightBox;
    Gtk::Image logo;
    Gtk::Image logo2;
    Gtk::Button disconnect;
    Gtk::Box filler;
    Gtk::Grid grid;
    Gtk::Button generate;
    Gtk::Label loggedUser;
    Gtk::Button addLogs;
};

#endif // GTKMM_CLIENT_H