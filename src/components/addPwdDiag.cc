#include "addPwdDiag.h"

addPwdDiag::addPwdDiag()
{
    for (Gtk::Widget *widget : widgets)
    {
        mainBox.pack_start(*widget, Gtk::PACK_SHRINK);
        widget->set_halign(Gtk::Align::ALIGN_CENTER);
        widget->override_color(textColor);
    }

    add.override_background_color(buttonColor);
    cancel.override_background_color(buttonColor);

    get_content_area()->add(mainBox);
    show_all_children();
    set_default_size(300, 300);
    override_background_color(backgroundColor2);

    add.signal_clicked().connect([this]()
                                 {
        if(wbEntry.get_text().empty() || usrEntry.get_text().empty() || pwdEntry.get_text().empty())
        {
            show_alert("Please fill all the fields",this);
            return;
        }
        
        //clt.add_passwordBlock(usrEntry.get_text(), pwdEntry.get_text(), wbEntry.get_text());
        close(); });

    cancel.signal_clicked().connect(sigc::mem_fun(this, &Gtk::Dialog::close));
    this->set_resizable(false);
    this->set_title("Add password");
    this->set_halign(Gtk::ALIGN_CENTER);
    this->set_valign(Gtk::ALIGN_CENTER);
    this->get_content_area()->set_orientation(Gtk::ORIENTATION_VERTICAL);

    this->show_all_children();
}

addPwdDiag::~addPwdDiag()
{
}


