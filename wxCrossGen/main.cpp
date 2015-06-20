#include <wx/wx.h>
#include <wx/fileconf.h>

#include "fsettings.hpp"
#include "fmain.hpp"

class MyApp: public wxApp {
public:
    bool OnInit();
protected:
    wxLocale m_locale;  // locale we'll be using
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    m_locale.Init();
#ifdef APP_LOCALE_DIR
    m_locale.AddCatalogLookupPathPrefix(wxT(APP_LOCALE_DIR));
#endif
    m_locale.AddCatalog(wxT(APP_CATALOG));

    SetAppName(wxT("CrossGen"));
    
    wxInitAllImageHandlers();
    wxConfigBase *config = new wxFileConfig;
    wxConfigBase::Set(config);
    MainFrame* fMain = new MainFrame(NULL);
    SetTopWindow(fMain);
    fMain->Show();
    return true;
}
