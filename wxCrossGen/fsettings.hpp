#ifndef FSETTINGS_HPP
#define FSETTINGS_HPP

#include <wx/wx.h>
#include <wx/wfstream.h>

#include "fbgui/fbgui.h"

class SettingsDialog: public VSettingsDialog {
    public:
        void onDictPathClick(wxCommandEvent& event);
        void onCancelClick(wxCommandEvent& event) {
            EndModal(wxID_CANCEL);
        }
		void onOkClick(wxCommandEvent& event);
        
        SettingsDialog( wxWindow* parent ) : VSettingsDialog(parent) {};
        
        wxString getDictPath() {
            return tDictPath->GetValue();
        }
        void setDictPath(wxString path) {
            tDictPath->SetValue(path);
        }
};

#endif // FSETTINGS_HPP
