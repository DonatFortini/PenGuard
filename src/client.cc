#include "client.h"

Client::Client(std::string login)
{
    set_icon_from_file("src/assets/logo120x120.png");
    this->logged_user = login;
    set_name("PenGuard");
    set_title("PenGuard");
    set_default_size(1200, 800);                       // width, height
    set_position(Gtk::WindowPosition::WIN_POS_CENTER); // center of screen

    buttonColor.set_rgba(182 / 255.0, 187 / 255.0, 196 / 255.0, 1.0);
    textColor.set_rgba(240 / 255.0, 236 / 255.0, 229 / 255.0, 1.0);
    backgroundColor.set_rgba(22 / 255.0, 26 / 255.0, 48 / 255.0, 1.0);
    backgroundColor2.set_rgba(49 / 255.0, 48 / 255.0, 77 / 255.0, 1.0);

    mainBox.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
    add(mainBox);

    // Left side
    leftBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    leftBox.set_size_request(300, 800);
    leftBox.set_spacing(20);

    logo.set("src/assets/logo120x120.png");
    loggedUser.set_text("Logged as: " + login);
    loggedUser.set_halign(Gtk::Align::ALIGN_CENTER);
    loggedUser.override_color(textColor);

    disconnect.set_label("Disconnect");
    disconnect.set_halign(Gtk::Align::ALIGN_CENTER);
    disconnect.override_background_color(buttonColor);
    disconnect.override_color(textColor);
    disconnect.signal_clicked().connect(sigc::mem_fun(*this, &Client::disconnect_user));

    filler.set_size_request(300, 500);

    generate.set_label("Generate logs");
    generate.set_halign(Gtk::Align::ALIGN_START);
    generate.set_valign(Gtk::Align::ALIGN_END);
    generate.override_background_color(buttonColor);
    generate.override_color(textColor);
    generate.signal_clicked().connect(sigc::mem_fun(*this, &Client::generate_logs));

    leftBox.add(logo);
    leftBox.add(loggedUser);
    leftBox.add(disconnect);
    leftBox.add(filler);
    leftBox.add(generate);

    leftBox.override_background_color(backgroundColor);

    // Right side
    rightBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    rightBox.set_size_request(900, 800);
    rightBox.set_spacing(20);

    grid.set_row_spacing(10);
    grid.set_size_request(900, 700);

    Gtk::Image *al = Gtk::make_managed<Gtk::Image>("src/assets/add.svg");
    addLogs.set_image(*al);
    addLogs.set_always_show_image(true);
    addLogs.set_halign(Gtk::Align::ALIGN_END);
    addLogs.set_valign(Gtk::Align::ALIGN_END);
    addLogs.override_background_color(buttonColor);
    addLogs.signal_clicked().connect(sigc::mem_fun(*this, &Client::add_password));

    rightBox.add(grid);
    rightBox.add(addLogs);
    rightBox.override_background_color(backgroundColor2);

    // mainBox is the main container
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

    container.set_size_request(100, 100);
    container.set_halign(Gtk::Align::ALIGN_CENTER);
    container.show();
    grid.attach(container, 0, 0, 1, 1);
}

void Client::edit_field(Gtk::Entry &username, Gtk::Entry &password, Gtk::Entry &website)
{
}

void Client::disconnect_user()
{
    Gtk::Dialog dialog("Disconnect", *this);
    Gtk::Label label("Are you sure you want to disconnect?");
    Gtk::Button disconnectButton("Disconnect");
    Gtk::Button cancelButton("Cancel");
    Gtk::Box dialogContent(Gtk::ORIENTATION_VERTICAL, 10);

    dialogContent.pack_start(label, Gtk::PACK_SHRINK);
    dialogContent.pack_start(disconnectButton, Gtk::PACK_SHRINK);
    dialogContent.pack_start(cancelButton, Gtk::PACK_SHRINK);

    disconnectButton.set_halign(Gtk::Align::ALIGN_CENTER);
    disconnectButton.override_background_color(buttonColor);
    disconnectButton.override_color(textColor);
    cancelButton.set_halign(Gtk::Align::ALIGN_CENTER);
    cancelButton.override_background_color(buttonColor);
    cancelButton.override_color(textColor);
    label.set_halign(Gtk::Align::ALIGN_CENTER);
    label.override_color(textColor);

    dialog.get_content_area()->add(dialogContent);
    dialog.set_default_size(400, 100);
    dialog.show_all_children();
    dialog.override_background_color(backgroundColor2);

    // disconnectButton.signal_clicked().connect(sigc::mem_fun(dialog, &Gtk::Dialog::close));
    cancelButton.signal_clicked().connect(sigc::mem_fun(dialog, &Gtk::Dialog::close));

    dialog.run();
}

void Client::generate_logs()
{
    Gtk::Dialog dialog("Random logs", *this);
    Gtk::Label label("Username:");
    Gtk::Entry entry;
    Gtk::Label label2("Password:");
    Gtk::Entry entry2;
    Gtk::Box dialog_content(Gtk::ORIENTATION_VERTICAL, 10);
    entry.set_text(logged_user + "@gmail.com");
    entry2.set_text(generate_password());

    dialog_content.pack_start(label, Gtk::PACK_SHRINK);
    dialog_content.pack_start(entry, Gtk::PACK_SHRINK);
    dialog_content.pack_start(label2, Gtk::PACK_SHRINK);
    dialog_content.pack_start(entry2, Gtk::PACK_SHRINK);

    dialog.get_content_area()->add(dialog_content);
    dialog.show_all_children();
    dialog.set_default_size(300, 150);
    dialog.override_background_color(backgroundColor2);
    dialog.run();
}

std::string Client::generate_password(void)
{
    std::string carac = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$%&*|!^-_.:;@#";
    std::string password;
    int pos;
    for (int i = 0; i < 10; ++i)
    {
        pos = rand() % carac.size();
        password += carac[pos];
    }

    return password;
}
