#include "manager.h"
#include "client.h"

#include <gtkmm/application.h>

void change_mainWindow(Glib::RefPtr<Gtk::Application> app, Manager &manager, const std::string &emission)
{
    manager.hide();
    app->hold();
    app->remove_window(manager);
    Client *client = new Client(emission);
    app->add_window(*client);
    app->release();
}

int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
    Manager manager;
    std::string emissionString;
    manager.logged_signal().connect([&app, &manager](const std::string &emission)
                                    { change_mainWindow(app, manager, emission); });

    return app->run(manager, argc, argv);
}