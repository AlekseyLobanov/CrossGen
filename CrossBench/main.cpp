#include "wx/wx.h"

#include <wx/app.h>
#include <wx/cmdline.h>

#include "crossbasetypes.hpp"
#include "crossgen.hpp"

/* To-Do:
 * Console app that runs generating of crosswords
 * with random or not. And if yes with command-line parametrs we can
 * set number of tests and get
 * 1. Worst, Best
 * 2. Mean
 * 3. Dispersion
 */

static const wxCmdLineEntryDesc cmdLineDesc[] = {
    { wxCMD_LINE_PARAM , wxT(""), wxT(""), wxT("cross_path"), 
        wxCMD_LINE_VAL_STRING },
    { wxCMD_LINE_PARAM, wxT(""), wxT(""), wxT("dict_path"),
        wxCMD_LINE_VAL_STRING },
    { wxCMD_LINE_OPTION, wxT("c"), wxT("count"), wxT("times to run generation, default = 10") ,
        wxCMD_LINE_VAL_NUMBER },
    { wxCMD_LINE_SWITCH, wxT("h"), wxT("help"), wxT("show this help message"),
        wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP },
    { wxCMD_LINE_NONE }
};

int main(int argc, char **argv) {
    wxInitializer wx_initializer;
    if ( !wx_initializer ) {
        fprintf(stderr, "Failed to initialize the wxWidgets library, aborting.");
        return -1;
    }
    wxCmdLineParser cmd_parser(cmdLineDesc, argc, argv);
    long run_count = 10;
    wxString cross_path, dict_path;
    switch ( cmd_parser.Parse() ) {
        case -1:
            return 0;
        case 0:
            cmd_parser.Found(wxT("count"), &run_count);
            cross_path = cmd_parser.GetParam(0);
            dict_path = cmd_parser.GetParam(1);
            wxPrintf(wxT("cross_path = ") + cross_path + wxT("\n"));
            wxPrintf(wxT("dict_path = ") + dict_path + wxT("\n"));
            wxPrintf(wxT("run_count = %d\n"), run_count);
            break;
        default:
            return 0;
    }
    

    return 0;
}
