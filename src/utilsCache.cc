#include "utilsCache.h"

Gdk::RGBA backgroundColor = Gdk::RGBA("rgb(22, 26, 48)");
Gdk::RGBA backgroundColor2 = Gdk::RGBA("rgb(49, 48, 77)");
Gdk::RGBA buttonColor = Gdk::RGBA("rgb(182, 187, 196)");
Gdk::RGBA textColor = Gdk::RGBA("rgb(0, 0, 0)");

void show_alert(const std::string &message, Gtk::Window *parent)
{
    Gtk::MessageDialog dialog(*parent, message, false, Gtk::MessageType::MESSAGE_ERROR, Gtk::ButtonsType::BUTTONS_OK, true);
    dialog.run();
}