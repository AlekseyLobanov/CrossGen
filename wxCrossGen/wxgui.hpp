#ifndef WXGUI_HPP
#define WXGUI_HPP

#include <ctime>
#include <map>
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/aboutdlg.h>

#include "crossgen.hpp"

#include "fbgui/fbgui.h"

#ifndef APP_CATALOG
#define APP_CATALOG "app"  // replace with the appropriate catalog name
#endif


class MainFrame: public VMainFrame {
protected:
    std::vector<wxString> _ans;
    std::vector<wxString> _ques;
    DictType              _dict;
    bool                  _isDictLoaded;
    AllWordsType          _allWords;
    CharsTransType        _transType;
    GridType              _grid;

public:
    void SetGridImage(GridType &grid, size_t w=400);

    MainFrame(
        wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxString& title = _("CrossGen"),
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxSize( 700,500 ),
        long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL )
            : VMainFrame(parent){

        _isDictLoaded = false;
        srand(time(NULL));
    }
    void onExitClick( wxCloseEvent& event ) { event.Skip(); }
    void onOpenGridClick( wxCommandEvent& event );
    void onGenerateClick( wxCommandEvent& event );
    void onExportClick( wxCommandEvent& event );
    void onExitClick( wxCommandEvent& event ) { event.Skip(); }
    void onAboutClick( wxCommandEvent& event ) {
        wxAboutDialogInfo info;
        info.AddDeveloper(_("AlekseyLobanov"));
        info.SetDescription(_("Simple GUI cross-generation application. Yet another bike"));
        info.SetName(wxTheApp->GetAppName());
        info.SetWebSite(wxT("http://likemath.ru"));
        wxAboutBox(info);
    }
};

#endif // WXGUI_HPP
