#include "manager.h"
#include "client.h"

#include <gtkmm/application.h>

void change_mainWindow(Glib::RefPtr<Gtk::Application> app, Manager &manager, const std::string &emission)
{
    app->hold();
    std::cout << "hold" << std::endl;
    app->remove_window(manager);
    std::cout << "creation client" << std::endl;
    Client client(emission);
    app->add_window(client);
    std::cout << "add client" << std::endl;
    manager.hide();
    std::cout << "release" << std::endl;
    app->release();
}

int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);

    Manager manager;
    std::string emissionString;
    manager.logged_signal().connect([&app, &manager](const std::string &emission)
                                    {
                                        change_mainWindow(app, manager, emission);
                                        std::cout << "func over" << std::endl; });

    app->run();
    app->add_window(manager);
}