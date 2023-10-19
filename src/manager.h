#ifndef GTKMM_MANAGER_H
#define GTKMM_MANAGER_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm.h>

#include <string.h>

class Manager : public Gtk::Window
{
private:
    /* data */
public:
    Manager(void);
    ~Manager();
};

#endif // GTKMM_MANAGER_H