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
protected:
    std::string logged_user;
};

#endif // GTKMM_CLIENT_H