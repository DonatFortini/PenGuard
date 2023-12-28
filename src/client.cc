#include "client.h"

Client::Client(std::string login) : logged_user(login),
                                    nb_passwords(0)
{
    set_icon_from_file("src/assets/logo120x120.png");
    set_name("PenGuard");
    set_title("PenGuard");
    set_default_size(1200, 800);                       // width, height
    set_position(Gtk::WindowPosition::WIN_POS_CENTER); // center of screen

    buttonColor.set_rgba(182 / 255.0, 187 / 255.0, 196 / 255.0, 1.0);
    textColor.set_rgba(0 / 255.0, 0 / 255.0, 0 / 255.0, 1.0);
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
    loggedUser.override_color(buttonColor);

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

    for (auto &widget : leftWidgets)
        leftBox.add(*widget);

    leftBox.override_background_color(backgroundColor);

    scrolledWindow.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC, Gtk::PolicyType::POLICY_AUTOMATIC);
    scrolledWindow.add(grid);
    grid.set_halign(Gtk::Align::ALIGN_CENTER);
    grid.set_valign(Gtk::Align::ALIGN_CENTER);
    grid.set_size_request(900, 700);
    scrolledWindow.set_size_request(900, 700);
    scrolledWindow.show_all_children();

    // Right side
    rightBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    rightBox.set_size_request(900, 800);
    rightBox.set_spacing(20);

    grid.set_row_spacing(45);

    Gtk::Image *al = Gtk::make_managed<Gtk::Image>("src/assets/add.svg");
    addLogs.set_image(*al);
    addLogs.set_always_show_image(true);
    addLogs.set_halign(Gtk::Align::ALIGN_END);
    addLogs.set_valign(Gtk::Align::ALIGN_END);
    addLogs.override_background_color(buttonColor);
    addLogs.signal_clicked().connect(sigc::mem_fun(*this, &Client::add_password));
    grid.override_background_color(backgroundColor2);
    rightBox.add(scrolledWindow);
    rightBox.add(addLogs);
    rightBox.override_background_color(backgroundColor2);

    // mainBox is the main container
    mainBox.pack_start(leftBox, Gtk::PackOptions::PACK_SHRINK);
    mainBox.add(rightBox);
    mainBox.set_halign(Gtk::Align::ALIGN_CENTER);
    mainBox.set_valign(Gtk::Align::ALIGN_CENTER);

    show_account(login);

    show_all();
}

Client::~Client(void)
{
}

void Client::show_alert(const std::string &message)
{
    Gtk::MessageDialog dialog(*this, message, false, Gtk::MessageType::MESSAGE_ERROR, Gtk::ButtonsType::BUTTONS_OK, true);
    dialog.run();
}

void Client::add_password(void)
{
    Gtk::Dialog dialog("Add password", *this);
    Gtk::Label label("Website:");
    Gtk::Entry entry;
    Gtk::Label label2("Username:");
    Gtk::Entry entry2;
    Gtk::Label label3("Password:");
    Gtk::Entry entry3;
    Gtk::Box dialog_content(Gtk::ORIENTATION_VERTICAL, 10);
    Gtk::Button add("Add");
    Gtk::Button cancel("Cancel");
    std::vector<Gtk::Widget *> widgets = {&label, &entry, &label2, &entry2, &label3, &entry3, &add, &cancel};

    for (auto &widget : widgets)
    {
        dialog_content.pack_start(*widget, Gtk::PACK_SHRINK);
        widget->set_halign(Gtk::Align::ALIGN_CENTER);
        widget->override_color(textColor);
    }

    add.override_background_color(buttonColor);
    cancel.override_background_color(buttonColor);

    dialog.get_content_area()->add(dialog_content);
    dialog.show_all_children();
    dialog.set_default_size(300, 300);
    dialog.override_background_color(backgroundColor2);

    add.signal_clicked().connect([&dialog, &entry, &entry2, &entry3, this]()
                                 {
        if(entry.get_text().empty() || entry2.get_text().empty() || entry3.get_text().empty())
        {
            show_alert("Please fill all the fields");
            return;
        }
        add_passwordBlock(entry2.get_text(), entry3.get_text(), entry.get_text());
        dialog.close(); });

    cancel.signal_clicked().connect(sigc::mem_fun(dialog, &Gtk::Dialog::close));

    dialog.run();
}

void Client::add_passwordBlock(std::string username, std::string password, std::string website)
{
    generate_block(username, password, website);
    Account acc = {username, password, website};
    add_account(acc);
}

void Client::generate_block(std::string username, std::string password, std::string website)
{
    passwordBlock *pb = Gtk::make_managed<passwordBlock>(username, password, website, logged_user);
    passwordBlocks.push_back(pb);
    Gtk::Box *box = Gtk::make_managed<Gtk::Box>();
    box->set_size_request(25, 80);
    grid.attach(*box, 0, nb_passwords, 1, 1);
    grid.attach(*pb, 1, nb_passwords, 1, 1);
    passwordBlocks[nb_passwords]->show_self();
    nb_passwords++;
    show_all_children();
}

void Client::show_account(std::string login)
{
    std::vector<Account> accounts = getUserPassword(login);
    if (accounts.empty())
        return;
    for (auto &account : accounts)
    {
        generate_block(account.username, account.password, account.website);
    }
}
// TODO
void Client::add_account(Account account)
{
    addUserPassword(logged_user, account.username, account.password, account.website);
}
// TODO
void Client::delete_account(Account account)
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
    // TODO
    //  disconnectButton.signal_clicked().connect(sigc::mem_fun(dialog, &Gtk::Dialog::close));
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
