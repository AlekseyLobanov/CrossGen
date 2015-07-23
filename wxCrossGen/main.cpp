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
    wxLocale::AddCatalogLookupPathPrefix(wxT("."));
#ifdef APP_LOCALE_DIR
    m_locale.AddCatalogLookupPathPrefix(wxT(APP_LOCALE_DIR));
#endif
    m_locale.AddCatalog(wxT(APP_CATALOG));
#ifdef __LINUX__
    {
        wxLogNull noLog;
        m_locale.AddCatalog(wxT("fileutils"));
    }
#endif

    SetAppName(wxT("CrossGen"));

    wxInitAllImageHandlers();
    wxConfigBase *config = new wxFileConfig;
    wxConfigBase::Set(config);
    MainFrame* fMain = new MainFrame(NULL);
    SetTopWindow(fMain);
    fMain->Show();
    return true;
}
