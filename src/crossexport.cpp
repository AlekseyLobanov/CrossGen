#include "crossexport.hpp"

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

wxString getGridString(const FilledCrossword &cross, wxChar space = wxT('-')){
    const wxString LINE_END = wxTextFile::GetEOL();
    
    wxString t_string;
    
    FilledCrossword t_cross(cross);
    if ( !t_cross.ans.empty() ) {
        fillCross(t_cross);
    }
    for (size_t i = 0; i < t_cross.grid.at(0).size(); ++i){
        for (size_t j = 0; j < t_cross.grid.size(); ++j){
            if ( t_cross.grid.at(j).at(i) == CELL_BORDER )
                t_string += space;
            else
                t_string += t_cross.grid.at(j).at(i);
        }
        t_string += LINE_END;
    }
    return t_string;
}

wxString getQuesString(const FilledCrossword &cross){
    const wxString LINE_END = wxTextFile::GetEOL();
    
    wxString t_string;
    
    if ( !cross.ques.empty() ) { // == print questions
        t_string += _("Vertical words:") + LINE_END;
            
        for (size_t i = 0; i < cross.words.size(); ++i){
            if (cross.words.at(i).direct == false)
                t_string += wxString::Format(wxT("%d. "), cross.words.at(i).ind) 
                  + cross.ques.at(i) + LINE_END;
        }
        
        t_string += _("Horisontal words:") + LINE_END;
        
        for (size_t i = 0; i < cross.words.size(); ++i){
            if (cross.words.at(i).direct == true)
                t_string += wxString::Format(wxT("%d. "), cross.words.at(i).ind) 
                  + cross.ques.at(i) + LINE_END;
        }
    }
    return t_string;
}

void exportToString(const FilledCrossword &cross, wxString &str_out, wxChar space = wxT('-')){
    str_out += getGridString(cross, space) + getQuesString(cross);
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
