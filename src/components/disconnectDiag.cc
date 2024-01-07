#include "disconnectDiag.h"

DisconnectDiag::DisconnectDiag()
{
    set_title("Disconnect");
    set_default_size(400, 100);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER);
    set_modal(true);
    set_resizable(false);
    set_border_width(10);
    set_deletable(false);
    override_background_color(backgroundColor2);

    label.set_text("Are you sure you want to disconnect?");
    label.set_halign(Gtk::Align::ALIGN_CENTER);
    label.override_color(textColor);

    disconnectButton.set_label("Disconnect");
    disconnectButton.set_halign(Gtk::Align::ALIGN_CENTER);
    disconnectButton.override_background_color(buttonColor);
    disconnectButton.override_color(textColor);
    disconnectButton.signal_clicked().connect(sigc::mem_fun(*this, &DisconnectDiag::disconnect));

    cancelButton.set_label("Cancel");
    cancelButton.set_halign(Gtk::Align::ALIGN_CENTER);
    cancelButton.override_background_color(buttonColor);
    cancelButton.override_color(textColor);
    cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &DisconnectDiag::close));

    dialogContent.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    dialogContent.set_spacing(10);
    dialogContent.pack_start(label, Gtk::PACK_SHRINK);
    dialogContent.pack_start(disconnectButton, Gtk::PACK_SHRINK);
    dialogContent.pack_start(cancelButton, Gtk::PACK_SHRINK);

    get_content_area()->add(dialogContent);
    show_all_children();
}

DisconnectDiag::~DisconnectDiag() {}

void DisconnectDiag::disconnect()
{
    dc.emit();
    close();
}

DisconnectDiag::dc_sig DisconnectDiag::dc_signal()
{
    return dc;
}