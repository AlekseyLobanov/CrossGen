#include "wx/wx.h"

#include <wx/app.h>
#include <wx/cmdline.h>

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
    { wxCMD_LINE_OPTION, wxT("c"), wxT("count"), wxT("times to run generation, default = 10"),
        wxCMD_LINE_VAL_NUMBER },
    { wxCMD_LINE_SWITCH, wxT("r"), wxT("rand"), wxT("enables generating random crosswords"),
        wxCMD_LINE_VAL_NONE },
    { wxCMD_LINE_SWITCH, wxT("v"), wxT("verbose"), wxT("enables verbose mode"),
        wxCMD_LINE_VAL_NONE },
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
    
    bool is_rand    = false;
    bool is_verbose = false;
    
    switch ( cmd_parser.Parse() ) {
        case -1:
            return 0;
        case 0:
            cmd_parser.Found(wxT("count"), &run_count);
            is_rand    = cmd_parser.Found(wxT("rand"));
            is_verbose = cmd_parser.Found(wxT("verbose"));
            grid_path  = cmd_parser.GetParam(0);
            dict_path  = cmd_parser.GetParam(1);
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
    AllWordsType all_words;
    CharsTransType trans_type;
    
    readDict(dict_path, dict);
    generateAllWords(dict, all_words, trans_type);
    readGrid(grid_path, grid);
    
    if ( is_rand )
        srand(time(NULL));
    
    for (long i = 0; i < run_count; ++i) {
        if ( !is_rand )
            srand(42);
        words_out.clear();
        durs.at(i) = wxGetLocalTimeMillis();
        generateCross(grid,all_words,trans_type,words_out);
        if ( words_out.size() == 0 )
            wxPrintf(wxT("Error in creating #%i!\n"),i+1);
        durs.at(i) = wxGetLocalTimeMillis() - durs.at(i);
        if ( is_verbose )
            wxPrintf(wxT("Time to generate #%i is ") 
                + durs.at(i).ToString() + wxT(" ms\n"), i+1);
    }
    wxLongLong tm_total = std::accumulate(durs.begin(),durs.end(), wxLongLong(0,0));
    wxLongLong tm_mean  = (tm_total + run_count/2) / run_count;
    wxPrintf(wxT("Total time = ") + tm_total.ToString() + wxT(" ms.\nMean time  = ") 
        + tm_mean.ToString() + wxT(" ms.\n"));
    return 0;
}
