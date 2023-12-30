#ifndef PASSWORDBLOCK_H
#define PASSWORDBLOCK_H
#include <gtkmm.h>
#include <gtkmm/dialog.h>
#include <string>

#include "../../db/db.h"

class passwordBlock : public Gtk::Box
{
public:
    passwordBlock(std::string username_string, std::string password_string, std::string website_string, std::string user_id_string);
    ~passwordBlock();
    passwordBlock();
    void delete_self(void);
    void edit_self(void);
    void show_password(void);
    std::string user_id;
    void show_self(void);

protected:
    Gdk::RGBA backgroundColor;
    Gdk::RGBA backgroundColor2;
    Gdk::RGBA buttonColor;
    Gdk::RGBA textColor;
    Gtk::Box fieldContainer = Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
    Gtk::Box buttonContainer = Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
    Gtk::Label username = Gtk::Label("Username");
    Gtk::Label password = Gtk::Label("Password");
    Gtk::Label website = Gtk::Label("Website");
    Gtk::Entry usernameEntry = Gtk::Entry();
    Gtk::Entry passwordEntry = Gtk::Entry();
    Gtk::Entry websiteEntry = Gtk::Entry();
    Gtk::Button deleteButton = Gtk::Button("Delete");
    Gtk::Button editButton = Gtk::Button("Edit");
    Gtk::Button showButton = Gtk::Button("Show");
    std::vector<Gtk::Widget *> fl = {&username, &usernameEntry, &password, &passwordEntry, &website, &websiteEntry};
    std::vector<Gtk::Entry *> field = {&usernameEntry, &passwordEntry, &websiteEntry};
    std::vector<Gtk::Widget *> bl = {&deleteButton, &editButton, &showButton};
};

#endif // !PASSWORDBLOCK_H