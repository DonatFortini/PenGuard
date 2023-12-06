#ifndef GTKMM_CLIENT_H
#define GTKMM_CLIENT_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm.h>

#include "../db/db.h"
#include "components/passwordBlock.h"

class Client : public Gtk::Window
{
public:
    Client(std::string login);
    ~Client();
    void add_password(void);
    void edit_field(Gtk::Entry &username, Gtk::Entry &password, Gtk::Entry &website);
    void disconnect_user(void);
    void generate_logs(void);
    void show_alert(const std::string &message);
    std::string generate_password(void);

protected:
    Gdk::RGBA backgroundColor;
    Gdk::RGBA backgroundColor2;
    Gdk::RGBA buttonColor;
    Gdk::RGBA textColor;
    std::string logged_user;
    Gtk::Box mainBox;
    Gtk::Box leftBox;
    Gtk::Image logo;
    Gtk::Button disconnect;
    Gtk::Box filler;
    Gtk::Button generate;
    Gtk::Label loggedUser;
    Gtk::Box rightBox;
    Gtk::Grid grid;
    Gtk::Button addLogs;
    passwordBlock *pb1;
    passwordBlock *pb2;
    passwordBlock *pb3;
    passwordBlock *pb4;
    passwordBlock *pb5;
    std::vector<passwordBlock *> passwordBlocks = {pb1, pb2, pb3, pb4, pb5};
    int nb_passwords;
};

#endif // GTKMM_CLIENT_H