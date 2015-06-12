#include "wx/wx.h"

#include <wx/app.h>
#include <wx/cmdline.h>
//#include <wx/time.h> 

#include "crossbasetypes.hpp"
#include "crossgen.hpp"

/* To-Do:
 * Console app that runs generating of crosswords
 * with random or not. And if yes with command-line parametrs we can
 * set number of tests and get
 * 3. Dispersion
 */

static const wxCmdLineEntryDesc cmdLineDesc[] = {
    { wxCMD_LINE_PARAM , wxT(""), wxT(""), wxT("grid_path"), 
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
    wxString grid_path, dict_path;
    switch ( cmd_parser.Parse() ) {
        case -1:
            return 0;
        case 0:
            cmd_parser.Found(wxT("count"), &run_count);
            grid_path = cmd_parser.GetParam(0);
            dict_path = cmd_parser.GetParam(1);
            wxLogDebug(wxT("grid_path = ") + grid_path + wxT("\n"));
            wxLogDebug(wxT("dict_path = ") + dict_path + wxT("\n"));
            wxLogDebug(wxT("run_count = %d\n"), run_count);
            break;
        default:
            return 0;
    }
    std::vector< wxLongLong > durs(run_count); // durations
    std::vector< wxString > words_out;
    DictType dict;
    GridType grid;
    
    readDict(dict_path, dict);
    readGrid(grid_path, grid);

    for (long i = 0; i < run_count; ++i) {
        words_out.clear();
        durs.at(i) = wxGetLocalTimeMillis();
        generateCross(grid,dict,words_out);
        if ( words_out.size() == 0 )
            wxPrintf(wxT("Error in creating crossword #%l!\n"),i);
        durs.at(i) = wxGetLocalTimeMillis() - durs.at(i);
    }
    wxLongLong tm_total = std::accumulate(durs.begin(),durs.end(), wxLongLong(0,0));
    wxLongLong tm_mean  = tm_total / run_count;
    wxPrintf(wxT("Total time = ") + tm_total.ToString() + wxT(" ms.\nMean time  = ") 
        + tm_mean.ToString() + wxT(" ms.\n"));
    return 0;
}
