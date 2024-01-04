#include "passwordBlock.h"

passwordBlock::passwordBlock(std::string username_string, std::string password_string, std::string website_string, std::string user_id_string)
{
    this->user_id = user_id_string;

    usernameEntry.set_text(username_string);
    passwordEntry.set_text(password_string);
    websiteEntry.set_text(website_string);

    passwordEntry.set_visibility(false);

    for (Gtk::Widget *x : fl)
        fieldContainer.add(*x);

    for (Gtk::Widget *x : bl)
        buttonContainer.add(*x);

    for (Gtk::Widget *x : buttonContainer.get_children())
    {
        x->override_background_color(buttonColor);
        x->override_color(textColor);
        x->set_halign(Gtk::Align::ALIGN_CENTER);
        x->set_valign(Gtk::Align::ALIGN_CENTER);
    }

    for (Gtk::Entry *x : field)
    {
        x->set_editable(false);
        x->override_background_color(buttonColor);
        x->override_color(textColor);
    }

    for (Gtk::Widget *x : fieldContainer.get_children())
    {
        x->set_size_request(700 * 0.8, 15);
        x->set_halign(Gtk::Align::ALIGN_CENTER);
        x->set_valign(Gtk::Align::ALIGN_CENTER);
    }

    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    add(fieldContainer);
    add(buttonContainer);
    set_size_request(850, 225);
    fieldContainer.set_size_request(850 * 0.7, 225);
    buttonContainer.set_size_request(850 * 0.3, 225);

    buttonContainer.set_halign(Gtk::Align::ALIGN_END);
    buttonContainer.set_valign(Gtk::Align::ALIGN_CENTER);

    editButton.signal_clicked().connect(sigc::mem_fun(*this, &passwordBlock::edit_self));
    deleteButton.signal_clicked().connect(sigc::mem_fun(*this, &passwordBlock::delete_self));
    showButton.signal_clicked().connect(sigc::mem_fun(*this, &passwordBlock::show_password));

    override_background_color(backgroundColor);
}

passwordBlock::passwordBlock()
{
    passwordBlock("username", "password", "website", "user_id");
}

passwordBlock::~passwordBlock()
{
}

void passwordBlock::show_self(void)
{
    show_all();
    buttonContainer.show_all_children();
    fieldContainer.show_all_children();
}

void passwordBlock::delete_self(void)
{
    std::cout << "delete " << this->user_id << std::endl;
    bool x = deleteUserPassword(user_id, usernameEntry.get_text(), passwordEntry.get_text(), websiteEntry.get_text());
    if (x)
        delete this;
}

void passwordBlock::edit_self(void)
{
    Gtk::Dialog dialog;
    dialog.set_title("Edit");
    Gtk::Box box(Gtk::ORIENTATION_VERTICAL, 10);
    Gtk::Label username = Gtk::Label("Username");
    Gtk::Label password = Gtk::Label("Password");
    Gtk::Label website = Gtk::Label("Website");
    Gtk::Entry usernameEntry = Gtk::Entry();
    Gtk::Entry passwordEntry = Gtk::Entry();
    Gtk::Entry websiteEntry = Gtk::Entry();
    Gtk::Button editButton = Gtk::Button("Edit");
    Gtk::Button cancelButton = Gtk::Button("Cancel");
    Gtk::Box buttonContainer(Gtk::ORIENTATION_HORIZONTAL, 10);
    std::vector<Gtk::Widget *> fl = {&username, &usernameEntry, &password, &passwordEntry, &website, &websiteEntry};
    std::vector<Gtk::Entry *> field = {&usernameEntry, &passwordEntry, &websiteEntry};
    std::vector<Gtk::Widget *> bl = {&editButton, &cancelButton};
    for (Gtk::Widget *x : fl)
        box.add(*x);
    for (Gtk::Widget *x : bl)
        buttonContainer.add(*x);
    for (Gtk::Widget *x : buttonContainer.get_children())
    {
        x->override_background_color(buttonColor);
        x->override_color(textColor);
        x->set_halign(Gtk::Align::ALIGN_CENTER);
        x->set_valign(Gtk::Align::ALIGN_CENTER);
    }
    for (Gtk::Entry *x : field)
    {
        x->override_background_color(buttonColor);
        x->override_color(textColor);
    }
    for (Gtk::Widget *x : box.get_children())
    {
        x->set_size_request(700 * 0.8, 15);
        x->set_halign(Gtk::Align::ALIGN_CENTER);
        x->set_valign(Gtk::Align::ALIGN_CENTER);
    }
    editButton.set_halign(Gtk::Align::ALIGN_CENTER);
    cancelButton.set_halign(Gtk::Align::ALIGN_CENTER);
    editButton.signal_clicked().connect(sigc::mem_fun(*this, &passwordBlock::delete_self));
    cancelButton.signal_clicked().connect(sigc::mem_fun(dialog, &Gtk::Dialog::close));
    dialog.get_content_area()->add(box);
    dialog.get_content_area()->add(buttonContainer);
    dialog.show_all_children();
    dialog.set_default_size(300, 300);
    dialog.override_background_color(backgroundColor2);
    dialog.run();

    editUserPassword(user_id, this->usernameEntry.get_text(), this->passwordEntry.get_text(), this->websiteEntry.get_text(), usernameEntry.get_text(), passwordEntry.get_text(), websiteEntry.get_text());
    this->usernameEntry.set_text(usernameEntry.get_text());
    this->passwordEntry.set_text(passwordEntry.get_text());
    this->websiteEntry.set_text(websiteEntry.get_text());
}

void passwordBlock::show_password(void)
{
    (passwordEntry.get_visibility()) ? passwordEntry.set_visibility(false) : passwordEntry.set_visibility(true);
}