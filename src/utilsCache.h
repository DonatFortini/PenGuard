#ifndef UTILSCACHE_H
#define UTILSCACHE_H

#include <string>
#include <gtkmm.h>

extern Gdk::RGBA backgroundColor;
extern Gdk::RGBA backgroundColor2;
extern Gdk::RGBA buttonColor;
extern Gdk::RGBA textColor;

void show_alert(const std::string& message, Gtk::Window* parent);

#endif // !UTILSCACHE_H