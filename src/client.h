#ifndef GTKMM_CLIENT_H
#define GTKMM_CLIENT_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm.h>

#include "utilsCache.h"
#include "components/logGenDiag.h"
#include "components/addPwdDiag.h"
#include "components/passwordBlock.h"
#include "components/disconnectDiag.h"

class Client : public Gtk::Window
{
public:
    Client(std::string login);
    ~Client();
    void add_password(void);
    void add_password_dist(std::string wb, std::string usr, std::string pwd);
    void add_passwordBlock(std::string website, std::string username, std::string password);
    void show_account(std::string login);
    void add_account(Account account);
    void disconnect_user(void);
    void generate_block(std::string username, std::string password, std::string website);
    void generate_logs(void);
    using cl_ses = sigc::signal<void>;
    cl_ses cl_signal();
    void close_session();

protected:
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
    addPwdDiag *addPwd;
    logGenDiag *logGen;
    DisconnectDiag *dcDiag;
    cl_ses cl;
};

#endif // GTKMM_CLIENT_H