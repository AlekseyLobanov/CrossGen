#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <ctime>

#include <wx/wx.h>
#include <wx/wfstream.h>
#include <wx/textfile.h>
#include <wx/fileconf.h>

#include "fsettings.hpp"
#include "fmain.hpp"

#include "crossgen.hpp"
#include "crossexport.hpp"
#include "settingsconsts.hpp"

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
