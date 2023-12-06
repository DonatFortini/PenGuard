#include "passwordBlock.h"

passwordBlock::passwordBlock(std::string username_string, std::string password_string, std::string website_string)
{
    buttonColor.set_rgba(182 / 255.0, 187 / 255.0, 196 / 255.0, 1.0);
    textColor.set_rgba(0 / 255.0, 0 / 255.0, 0 / 255.0, 1.0);
    backgroundColor.set_rgba(22 / 255.0, 26 / 255.0, 48 / 255.0, 1.0);
    backgroundColor2.set_rgba(49 / 255.0, 48 / 255.0, 77 / 255.0, 1.0);

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
    }

    for(Gtk::Entry *x : field)
    {
        x->set_editable(false);
        x->override_background_color(buttonColor);
        x->override_color(textColor);
        x->set_size_request(700*0.8,20);
        x->set_halign(Gtk::Align::ALIGN_CENTER);
    }

    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    add(fieldContainer);
    add(buttonContainer);
    set_size_request(850, 80);
    fieldContainer.set_size_request(850 * 0.7, 80);
    buttonContainer.set_size_request(850 * 0.3, 80);

    buttonContainer.set_halign(Gtk::Align::ALIGN_END);
    buttonContainer.set_valign(Gtk::Align::ALIGN_CENTER);

    override_background_color(backgroundColor);
}

passwordBlock::passwordBlock()
{
    passwordBlock("username", "password", "website");
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