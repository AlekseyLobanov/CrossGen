#ifndef CROSSEXPORT_HPP
#define CROSSEXPORT_HPP

#include <wx/wx.h>

#include "crossbasetypes.hpp"

//wxTextFile::GetEOL()

void exportToString(const FilledCrossword &cross, const bool prn_ans, wxString &str_out){
    
}

bool exportToFile(const FilledCrossword &cross, const bool prn_ans, const wxString path){
    wxTextFile f(path);
    if ( f.Exists() )
        return false;
    f.Create();
    wxString cont;
    exportToString(cross, prn_ans, cont);
    f.AddLine(cont);
    f.Write();
    f.Close();
    return true;
}

#endif // CROSSEXPORT_HPP
