#include "client.h"

Client::Client(std::string login) : logged_user(login),
                                    nb_passwords(0)
{
    set_icon_from_file("src/assets/logo120x120.png");
    set_name("PenGuard");
    set_title("PenGuard");
    set_default_size(1200, 800);                       
    set_position(Gtk::WindowPosition::WIN_POS_CENTER);

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

void Client::add_password(void)
{
    addPwd = new addPwdDiag("", "", "");
    addPwd->addpwd_signal().connect(sigc::mem_fun(*this, &Client::add_passwordBlock));
    addPwd->run();
}

void Client::add_password_dist(std::string wb, std::string usr, std::string pwd)
{
    logGen->~logGenDiag();
    addPwd = new addPwdDiag(wb, usr, pwd);
    addPwd->addpwd_signal().connect(sigc::mem_fun(*this, &Client::add_passwordBlock));
    addPwd->run();
}

void Client::add_passwordBlock(std::string website, std::string username , std::string password)
{
    addPwd->~addPwdDiag();
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
        generate_block(account.username, account.password, account.website);
}

void Client::add_account(Account account)
{
    addUserPassword(logged_user, account.username, account.password, account.website);
}

void Client::disconnect_user()
{
    dcDiag = new DisconnectDiag();
    dcDiag->dc_signal().connect(sigc::mem_fun(*this, &Client::close_session));
    dcDiag->run();
}

void Client::close_session()
{
    dcDiag->~DisconnectDiag();
    cl.emit();
}

Client::cl_ses Client::cl_signal()
{
    return cl;
}

void Client::generate_logs(void)
{
    logGen = new logGenDiag(logged_user);
    logGen->loggen_signal().connect(sigc::mem_fun(*this, &Client::add_password_dist));
    logGen->run();
}
