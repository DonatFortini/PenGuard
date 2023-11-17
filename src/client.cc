#include "client.h"

Client::Client(std::string login)
{
    set_icon_from_file("src/assets/logo120x120.png");
    this->logged_user = login;
    set_name("PenGuard");
    set_title("PenGuard");
    set_default_size(1200, 800);                       // width, height
    set_position(Gtk::WindowPosition::WIN_POS_CENTER); // center of screen

    mainBox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
    add(mainBox);

    // Left side
    logo.set("src/assets/logo120x120.png");
    loggedUser.set_text("Logged as: " + login);
    disconnect.set_label("Disconnect");

    leftBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    leftBox.set_size_request(300, 800);
    leftBox.set_spacing(20);
    leftBox.add(logo);
    leftBox.add(loggedUser);
    leftBox.add(disconnect);
    leftBox.add(generate);
    generate.set_label("Generate logs");
    generate.set_halign(Gtk::Align::ALIGN_START);
    generate.set_valign(Gtk::Align::ALIGN_END);
    generate.signal_clicked().connect(sigc::mem_fun(*this, &Client::generate_logs));

    Gdk::RGBA backgroundColor;
    backgroundColor.set_rgba(0.0, 0.0, 0.0, 1.0); // Set the desired color values
    leftBox.override_background_color(backgroundColor);

    // Right side
    rightBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    rightBox.set_size_request(900, 800);
    rightBox.set_spacing(20);
    logo2.set("src/assets/logo240x240.png");
    rightBox.add(logo2);
    mainBox.pack_start(leftBox, Gtk::PackOptions::PACK_SHRINK);
    mainBox.add(rightBox);
    mainBox.set_halign(Gtk::Align::ALIGN_CENTER);
    mainBox.set_valign(Gtk::Align::ALIGN_CENTER);

    show_all();
}

Client::~Client(void)
{
}

void Client::add_password()
{
    Gtk::Box container;
    Gtk::Box fieldContainer;
    Gtk::Box buttonContainer;
    Gtk::Label username;
    Gtk::Label password;
    Gtk::Label website;
    Gtk::Entry usernameEntry;
    Gtk::Entry passwordEntry;
    Gtk::Entry websiteEntry;
    Gtk::Button deleteButton;
    Gtk::Button editButton;
    Gtk::Button showButton;

    container.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
    fieldContainer.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    buttonContainer.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    fieldContainer.set_spacing(10);

    username.set_text("Username");
    password.set_text("Password");
    website.set_text("Website");

    usernameEntry.set_editable(false);
    passwordEntry.set_editable(false);
    websiteEntry.set_editable(false);
    passwordEntry.set_visibility(false);

    fieldContainer.add(username);
    fieldContainer.add(usernameEntry);
    fieldContainer.add(password);
    fieldContainer.add(passwordEntry);
    fieldContainer.add(website);
    fieldContainer.add(websiteEntry);

    deleteButton.set_label("Delete");
    editButton.set_label("Edit");
    showButton.set_label("Show");
    buttonContainer.add(deleteButton);
    buttonContainer.add(editButton);
    buttonContainer.add(showButton);

    container.add(fieldContainer);
    container.add(buttonContainer);

    container.show_all_children();
    container.set_size_request(100, 100);
    rightBox.add(container);
}

void Client::edit_field(Gtk::Entry &username, Gtk::Entry &password, Gtk::Entry &website)
{
}

void Client::disconnect_user()
{
}

void Client::generate_logs()
{
    Gtk::Dialog dialog("Random logs", *this);
    Gtk::Label label("Username:");
    Gtk::Entry entry;
    Gtk::Label label2("Password:");
    Gtk::Entry entry2;
    Gtk::Box dialog_content(Gtk::ORIENTATION_VERTICAL, 10);
    entry.set_text(logged_user+"@gmail.com");
    entry2.set_text(generate_password());

    dialog_content.pack_start(label, Gtk::PACK_SHRINK);
    dialog_content.pack_start(entry, Gtk::PACK_SHRINK);
    dialog_content.pack_start(label2, Gtk::PACK_SHRINK);
    dialog_content.pack_start(entry2, Gtk::PACK_SHRINK);

    dialog.get_content_area()->add(dialog_content);
    dialog.show_all_children();

    dialog.run();
}

std::string Client::generate_password(void)
{
    std::string carac="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$%&*()[]{}@#";
    std::string password;
    int pos;
    for(int i=0;i<10;++i)
    {
        pos=rand()%carac.size();
        password+=carac[pos];
    }

    return password;
}
