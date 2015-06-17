#ifndef CROSSEXPORT_HPP
#define CROSSEXPORT_HPP

#include <wx/wx.h>

#include "crossbasetypes.hpp"

void fillCross(FilledCrossword &cross){
    for ( size_t i = 0; i < cross.words.size(); ++i ) {
        if ( cross.words.at(i).direct == true ) {
            for (size_t j = 0; j < cross.words.at(i).len; ++j){
                cross.grid.at(cross.words.at(i).x+j).at(cross.words.at(i).y) = cross.ans.at(i).at(j);
            }
        } else {
            for (size_t j = 0; j < cross.words.at(i).len; ++j)
                cross.grid.at(cross.words.at(i).x).at(cross.words.at(i).y+j) = cross.ans.at(i).at(j);
        }
    }
}

void exportToString(const FilledCrossword &cross, const bool prn_ans,
    wxString &str_out, wxChar space = wxT('-')){
    FilledCrossword t_cross(cross);
    if ( prn_ans && (t_cross.ans.size() != 0) ) {
        fillCross(t_cross);
    }
    wxLogDebug(wxT("3"));
    for (size_t i = 0; i < t_cross.grid.at(0).size(); ++i){
        wxString cur_line;
        for (size_t j = 0; j < t_cross.grid.size(); ++j){
            if ( t_cross.grid.at(j).at(i) == CELL_BORDER )
                cur_line += space;
            else
                cur_line += t_cross.grid.at(j).at(i);
        }
        cur_line += wxTextFile::GetEOL();
        
        str_out += cur_line;
    }
}

bool exportToFile(const FilledCrossword &cross, const bool prn_ans, const wxString path){
    wxTextFile f(path);
    if ( f.Exists() )
        return false;
    f.Create();
    f.Open(path);
    wxString cont;
    exportToString(cross, prn_ans, cont);
    f.AddLine(cont);
    f.Write();
    f.Close();
    return true;
}

#endif // CROSSEXPORT_HPP
