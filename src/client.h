#ifndef GTKMM_CLIENT_H
#define GTKMM_CLIENT_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm.h>


#include "components/passwordBlock.h"



class Client : public Gtk::Window
{
public:
        Client(std::string login);
    ~Client();
    void add_password(void);
    void add_passwordBlock(std::string username, std::string password, std::string website);
    void show_account(std::string login);
    void add_account(Account account);
    void delete_account(Account account);
    void disconnect_user(void);
    void generate_logs(void);
    void show_alert(const std::string &message);
    void generate_block(std::string username, std::string password, std::string website);
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
    Gtk::ScrolledWindow scrolledWindow;
    std::vector<passwordBlock *> passwordBlocks;
    std::vector<Gtk::Widget *> leftWidgets = {&logo, &loggedUser, &disconnect, &filler, &generate};
    int nb_passwords;
};

#endif // GTKMM_CLIENT_H