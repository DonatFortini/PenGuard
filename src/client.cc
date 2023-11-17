#include "client.h"

Client::Client(std::string login) 
{
    set_icon_from_file("src/assets/logo120x120.png");
    set_name("PenGuard");
    set_title("PenGuard");
    set_default_size(1200, 800);                       // width, height
    set_position(Gtk::WindowPosition::WIN_POS_CENTER); // center of screen
    show_all();
}

Client::~Client(void)
{
}




