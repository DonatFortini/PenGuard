#ifndef DISCONNECTDIAG_H
#define DISCONNECTDIAG_H
#include <gtkmm.h>
#include "../utilsCache.h"

class DisconnectDiag : public Gtk::Dialog
{
public:
    DisconnectDiag();
    virtual ~DisconnectDiag();
    void disconnect();
    using dc_sig = sigc::signal<void>;
    dc_sig dc_signal() ;
protected:
    Gtk::Label label;
    Gtk::Button disconnectButton;
    Gtk::Button cancelButton;
    Gtk::Box dialogContent;
    dc_sig dc;
};
#endif // !DISCONNECTDIAG_H
