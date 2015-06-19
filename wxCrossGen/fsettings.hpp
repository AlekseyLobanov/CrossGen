#ifndef FSETTINGS_HPP
#define FSETTINGS_HPP

#include <wx/wx.h>

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

void SettingsDialog::onDictPathClick(wxCommandEvent& event) {
    wxFileDialog dlgOpen(this, _("Open dictionary file"), wxEmptyString, wxEmptyString,
    _("Files of dictionaris (*.txt)|*.txt"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    
    if ( dlgOpen.ShowModal() == wxID_CANCEL )
        return;
        
    wxFileInputStream input_stream(dlgOpen.GetPath());
    if ( !input_stream.IsOk() ) {
        wxMessageBox(_("Cannot open dictionary file ") + dlgOpen.GetPath(), _("Error"), wxICON_ERROR);
        return;
    }
    tDictPath->SetValue(dlgOpen.GetPath());
}

void SettingsDialog::onOkClick(wxCommandEvent& event) {
    wxFileInputStream input_stream(tDictPath->GetValue());
    if ( !input_stream.IsOk() ) {
        wxMessageBox(_("Cannot open dictionary file ") + tDictPath->GetValue(), _("Error"), wxICON_ERROR);
        return;
    }
    EndModal(wxID_OK);
}

#endif
