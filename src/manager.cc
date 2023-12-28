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

    backgroundColor.set_rgba(22 / 255.0, 26 / 255.0, 48 / 255.0, 1.0);
    backgroundColor2.set_rgba(49 / 255.0, 48 / 255.0, 77 / 255.0, 1.0);
    buttonColor.set_rgba(182 / 255.0, 187 / 255.0, 196 / 255.0, 1.0);
    textColor.set_rgba(0 / 255.0, 0 / 255.0, 0 / 255.0, 1.0);

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
        show_alert("Veuillez remplir tous les champs");
        return;
    }
    // checkUser(login.get_text(), mdp.get_text()) ? logged.emit(login.get_text()) : show_alert("Login ou mot de passe incorrect");
    std::cout << "Login: " << encrypt(mdp.get_text()) << "-" << decrypt(encrypt(mdp.get_text())) << std::endl;
}

bool Manager::is_not_empty(void)
{
    return login.get_text() != "" && mdp.get_text() != "";
}

void Manager::show_alert(const std::string &message)
{
    Gtk::MessageDialog dialog(*this, message, false, Gtk::MessageType::MESSAGE_ERROR, Gtk::ButtonsType::BUTTONS_OK, true);
    dialog.run();
}

Manager::send Manager::logged_signal()
{
    return logged;
}
