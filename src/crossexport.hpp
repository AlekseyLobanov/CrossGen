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

void exportToString(const FilledCrossword &cross, wxString &str_out, wxChar space = wxT('-')){
    const wxString LINE_END = wxTextFile::GetEOL();
    
    FilledCrossword t_cross(cross);
    if ( t_cross.ans.size() != 0 ) {
        fillCross(t_cross);
    }
    for (size_t i = 0; i < t_cross.grid.at(0).size(); ++i){
        wxString cur_line;
        for (size_t j = 0; j < t_cross.grid.size(); ++j){
            if ( t_cross.grid.at(j).at(i) == CELL_BORDER )
                cur_line += space;
            else
                cur_line += t_cross.grid.at(j).at(i);
        }
        cur_line += LINE_END;
        
        str_out += cur_line;
    }
    if ( cross.ques.size() != 0 ) { // == print questions
        str_out += _("Vertical words:") + LINE_END;
            
        for (size_t i = 0; i < cross.words.size(); ++i){
            if (cross.words.at(i).direct == false)
                str_out += wxString::Format(wxT("%d. "), cross.words.at(i).ind) 
                  + cross.ques.at(i) + LINE_END;
        }
        
        str_out += _("Horisontal words:") + LINE_END;
        
        for (size_t i = 0; i < cross.words.size(); ++i){
            if (cross.words.at(i).direct == true)
                str_out += wxString::Format(wxT("%d. "), cross.words.at(i).ind) 
                  + cross.ques.at(i) + LINE_END;
        }
    }
}

bool exportToFile(const FilledCrossword &cross, const wxString path){
    wxTextFile f(path);
    if ( f.Exists() )
        return false;
    f.Create();
    f.Open(path);
    wxString cont;
    exportToString(cross, cont);
    f.AddLine(cont);
    f.Write();
    f.Close();
    return true;
}

#endif // CROSSEXPORT_HPP
