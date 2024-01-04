#include "logGenDiag.h"

logGenDiag::logGenDiag(std::string user_id_string)
{
    this->user_id = user_id_string;
    this->set_title("Random logs");
    this->set_halign(Gtk::ALIGN_CENTER);
    this->set_valign(Gtk::ALIGN_CENTER);
    this->set_resizable(false);
    this->set_size_request(300, 150);
    this->override_background_color(backgroundColor2);
    this->usrEntry.set_text(this->user_id + "@gmail.com");
    generate_password();
    for (Gtk::Widget *widget : this->widgets)
        this->fieldBox.pack_start(*widget, Gtk::PACK_SHRINK);
    this->fieldBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    this->fieldBox.set_spacing(10);
    buttons.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    buttons.set_spacing(10);
    buttons.pack_start(this->generate, Gtk::PACK_SHRINK);
    buttons.pack_end(this->create, Gtk::PACK_SHRINK);
    this->mainBox.pack_start(this->fieldBox, Gtk::PACK_SHRINK);
    this->mainBox.pack_end(this->buttons, Gtk::PACK_SHRINK);
    this->mainBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    this->mainBox.set_spacing(20);
    this->get_content_area()->add(this->mainBox);
    
    this->generate.signal_clicked().connect(sigc::mem_fun(*this, &logGenDiag::generate_password));

    this->show_all_children();
}

logGenDiag::logGenDiag()
{
    logGenDiag("test");
}

logGenDiag::~logGenDiag()
{
}

void logGenDiag::generate_password(void)
{
    std::string password;
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    for (int i = 0; i < 16; ++i)
        password += chars[rand() % chars.size()];
    this->pwdEntry.set_text(password);
}


