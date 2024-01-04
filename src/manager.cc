#include "manager.h"

Manager::Manager(void) : fieldBox(Gtk::Orientation::ORIENTATION_VERTICAL)
{
    set_icon_from_file("src/assets/logo120x120.png");
    set_name("PenGuard");
    set_title("PenGuard");
    set_default_size(400, 600);                        // width, height
    set_position(Gtk::WindowPosition::WIN_POS_CENTER); // center of screen

    add(mainBox);
    mainBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    mainBox.set_halign(Gtk::Align::ALIGN_CENTER);

    mainBox.add(logoBox);
    mainBox.add(fieldBox);

    logo.set("src/assets/logo240x240.png");
    logoBox.add(logo);
    logoBox.set_hexpand(true);

    mdp.set_placeholder_text("Mot de passe");
    mdp.set_hexpand(true);
    mdp.set_visibility(false);

    login.set_placeholder_text("Login");
    login.set_hexpand(true);

    validate.set_label("Valider");
    validate.set_hexpand(true);
    validate.signal_clicked().connect(sigc::mem_fun(*this, &Manager::on_validate_clicked));

    fieldBox.add(login);
    fieldBox.add(mdp);
    fieldBox.add(validate);

    mainBox.set_spacing(20);
    fieldBox.set_spacing(10);

    this->override_background_color(backgroundColor);

    login.override_background_color(backgroundColor2);
    login.override_color(textColor);
    mdp.override_background_color(backgroundColor2);
    mdp.override_color(textColor);
    validate.override_background_color(buttonColor);
    validate.override_color(textColor);
    mainBox.show_all();
}

Manager::~Manager()
{
}

void Manager::on_validate_clicked()
{
    if (!is_not_empty())
    {
        show_alert("Veuillez remplir tous les champs", this);
        return;
    }
    checkUser(login.get_text(), mdp.get_text()) ? logged.emit(login.get_text()) : show_alert("Login ou mot de passe incorrect", this);
}

bool Manager::is_not_empty(void)
{
    return login.get_text() != "" && mdp.get_text() != "";
}

Manager::send Manager::logged_signal()
{
    return logged;
}
