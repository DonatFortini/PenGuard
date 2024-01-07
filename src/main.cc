#include "manager.h"
#include "client.h"

#include <gtkmm/application.h>
#include <memory>

int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);

    auto manager = std::make_shared<Manager>();

    std::string emissionString;
    manager->logged_signal().connect([app, manager, &emissionString](const std::string &emission)
    {
        manager->hide();

        auto client = std::make_shared<Client>(emission);
        app->add_window(*client);

        client->cl_signal().connect([app, manager, client]()
        {
            app->hold();
            app->remove_window(*client);
            std::cout << "Closing client..." << std::endl;
            client->~Client();
            std::cout << "Clos..." << std::endl;
            std::cout << "folo." << std::endl;
            manager->show();
            app->add_window(*manager);
            std::cout << "folsssso." << std::endl;
            app->release();
            //TODO : fix seg fault when disconnecting
        });
        
    });

    return app->run(*manager, argc, argv);
}
