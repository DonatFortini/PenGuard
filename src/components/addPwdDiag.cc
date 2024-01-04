#include "addPwdDiag.h"

addPwdDiag::addPwdDiag()
{
    this->fieldBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    
    for (Gtk::Widget *widget : widgets)
    {
        this->fieldBox.pack_start(*widget, Gtk::PACK_SHRINK);
        widget->set_halign(Gtk::Align::ALIGN_CENTER);
        widget->override_color(textColor);
    }

    this->buttonBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->buttonBox.set_spacing(10);
    this->buttonBox.set_halign(Gtk::Align::ALIGN_CENTER);
    this->buttonBox.pack_start(add, Gtk::PACK_SHRINK);
    this->buttonBox.pack_end(cancel, Gtk::PACK_SHRINK);
    this->fieldBox.pack_end(buttonBox, Gtk::PACK_SHRINK);
    this->add.override_background_color(buttonColor);
    this->cancel.override_background_color(buttonColor);

    get_content_area()->add(fieldBox);
    show_all_children();
    
    override_background_color(backgroundColor2);
    
    this->add.signal_clicked().connect([this]()
                                 {
        if(wbEntry.get_text().empty() || usrEntry.get_text().empty() || pwdEntry.get_text().empty())
        {
            show_alert("Please fill all the fields",this);
            return;
        }
        
        //TODO : add signal connect to manager
        close(); });

    cancel.signal_clicked().connect(sigc::mem_fun(this, &Gtk::Dialog::close));

    this->set_resizable(false);
    this->set_title("Add password");
    this->set_size_request(450,150);
    this->set_halign(Gtk::Align::ALIGN_CENTER);
    this->set_valign(Gtk::Align::ALIGN_CENTER);
    this->get_content_area()->set_orientation(Gtk::ORIENTATION_VERTICAL);

    this->show_all_children();
}

addPwdDiag::addPwdDiag(std::string wb, std::string usr, std::string pwd)
{
    addPwdDiag();
    this->wbEntry.set_text(wb);
    this->usrEntry.set_text(usr);
    this->pwdEntry.set_text(pwd);
}

addPwdDiag::~addPwdDiag()
{
}
