#include "fsettings.hpp"

void SettingsDialog::onDictPathClick(wxCommandEvent& event) {
    wxFileDialog dlgOpen(this, _("Open dictionary file"), wxEmptyString, wxEmptyString,
    _("Files of dictionaries (*.txt)|*.txt"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    
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
