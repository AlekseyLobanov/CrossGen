#ifndef FMAIN_HPP
#define FMAIN_HPP


#include <ctime>
#include <map>
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/aboutdlg.h>
#include <wx/fileconf.h>

#include "fbgui/fbgui.h"

#include "settingsconsts.hpp"
#include "crossgen.hpp"
#include "crossexport.hpp"
#include "fsettings.hpp"

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
    void procDict(wxString path);
    void saveConfig();
    
    MainFrame( wxWindow* parent);
    void onWindowClose( wxCloseEvent& event );
    void onOpenGridClick( wxCommandEvent& event );
    void onGenerateClick( wxCommandEvent& event );
    void onSettingsClick( wxCommandEvent& event );
    void onExportClick( wxCommandEvent& event );
    void onExitClick( wxCommandEvent& event );
    void onAboutClick( wxCommandEvent& event ) {
        wxAboutDialogInfo info;
        info.AddDeveloper(_("Aleksey Lobanov"));
        info.SetDescription(_("Simple GUI cross-generation application. Yet another bike"));
        info.SetName(wxTheApp->GetAppName());
        info.SetWebSite(wxT("http://likemath.ru"));
        wxAboutBox(info);
    }
};

#endif // FMAIN_HPP
