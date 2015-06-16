#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <ctime>

#include <wx/wx.h>
#include <wx/wfstream.h>
#include <wx/textfile.h>
#include "wxgui.hpp"

#include "crossgen.hpp"
#include "crossexport.hpp"


void MainFrame::onOpenGridClick(wxCommandEvent &event) {
    wxFileDialog dlgOpen(this, _("Open crossword file"), wxEmptyString, wxEmptyString,
    wxT("Files of crossword (*.cross)|*.cross"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    
    if ( dlgOpen.ShowModal() == wxID_CANCEL )
        return;
    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(dlgOpen.GetPath());
    if ( !input_stream.IsOk() ) {
        wxLogError(wxT("Cannot open file ")+dlgOpen.GetPath());
        return;
    }
    tPath->SetValue(dlgOpen.GetPath());
    GridType grid;
    readGrid(tPath->GetValue(), grid);
    SetGridImage(grid);
}

void MainFrame::SetGridImage(GridType &grid, size_t w) {
    size_t h = static_cast<float>(w) / grid.size() * grid.at(0).size();
    wxBitmap bmp(w, h);
    wxMemoryDC dc;
    dc.SelectObject(bmp);
    dc.Clear();
    
    std::vector<WordInfo> winfos;
    generateWordInfo(grid, winfos);
    
    float sq_w = static_cast<int>(static_cast<float>(w) / grid.size());
    float sq_h = static_cast<int>(static_cast<float>(h) / grid.at(0).size());
    
    wxFont cur_f = dc.GetFont();
    cur_f.SetPointSize(sq_h/3);
    
    dc.SetBrush(wxBrush(wxColour(217,231,200)));
    dc.SetFont(cur_f);
    
    for (size_t i = 0; i < grid.size(); ++i){
        for (size_t j = 0; j < grid.at(0).size(); ++j){
            if (grid.at(i).at(j) == CELL_CLEAR)
                dc.DrawRectangle(sq_w*i,sq_h*j,sq_w+1,sq_h+1);
        }
    }
    
    for (size_t i = 0; i < winfos.size(); ++i) {
        dc.DrawText(wxString::Format(wxT("%d"),winfos.at(i).ind), sq_w*winfos.at(i).x, sq_h*winfos.at(i).y);
    }
    
    if ( _words.size() > 0 ) {
        using std::vector;
        vector< vector< bool > > usedCells(
            grid.size(), 
            vector<bool>(grid.at(0).size(), false)
        );
        cur_f = dc.GetFont();
        cur_f.SetPointSize(sq_h*0.6);
        dc.SetFont(cur_f);
        for ( size_t i = 0; i < winfos.size(); ++i ) {
            if ( winfos.at(i).direct == true ) {
                for (size_t j = 0; j < winfos.at(i).len; ++j)
                    if ( !usedCells.at(winfos.at(i).x+j).at(winfos.at(i).y) ) {
                        dc.DrawText(
                            _words.at(i).at(j),
                            sq_w*(winfos.at(i).x+j) + sq_w*0.24,
                            sq_h*winfos.at(i).y
                        );
                        usedCells.at(winfos.at(i).x+j).at(winfos.at(i).y) = true;
                    }
            } else {
                for (size_t j = 0; j < winfos.at(i).len; ++j)
                    if ( !usedCells.at(winfos.at(i).x).at(winfos.at(i).y+j) ) {
                        dc.DrawText(
                            _words.at(i).at(j),
                            sq_w*winfos.at(i).x + sq_w*0.24,
                            sq_h*(winfos.at(i).y+j)
                        );
                        usedCells.at(winfos.at(i).x).at(winfos.at(i).y+j) = true;
                    }
            }
        }
    }
    
    bPreview->SetBitmap(bmp);
    
    dc.SelectObject( wxNullBitmap );
    
    this->Refresh();
}

void MainFrame::onGenerateClick(wxCommandEvent &event) {
    if ( !_isDictLoaded ) {
        readDict(wxT("big_cross_ru.txt"), _dict);
        generateAllWords(_dict, _allWords, _transType);
        _isDictLoaded = true;
    }
    
    std::vector<wxString> words_out;
    GridType grid;
    if (tPath->GetValue() == wxEmptyString){
        wxMessageBox( wxT("Не указана путь к сетке"), wxT("Инфо"), wxICON_INFORMATION);
        return;
    }
    readGrid(tPath->GetValue(), grid);
    try{
        generateCross(grid, _allWords, _transType, words_out);
        
        _words.clear();
        _words = words_out;
        
        std::vector<WordInfo> winfos;
        generateWordInfo(grid, winfos);
        
        tOutput->Clear();
        
        tOutput->AppendText(wxT("По вертикали:\n"));
        
        for (size_t i = 0; i < words_out.size(); ++i){
            if (winfos.at(i).direct == false)
                tOutput->AppendText(wxString::Format(wxT("%d. "), winfos.at(i).ind) 
                  + _dict[words_out.at(i)] +wxT("\n"));
        }
        
        tOutput->AppendText(wxT("По горизонтали:\n"));
        
        for (size_t i = 0; i < words_out.size(); ++i){
            if (winfos.at(i).direct == true)
                tOutput->AppendText(wxString::Format(wxT("%d. "), winfos.at(i).ind) 
                  + _dict[words_out.at(i)]+wxT("\n"));
        }
        if (winfos.size() == 0) 
            throw 42;
        SetGridImage(grid);
        _words.clear();
    }
    catch ( ... ){
        tOutput->Clear();
        wxMessageBox( wxT("Не могу создать кроссворд"), wxT("Ошибка"), wxICON_ERROR );
    }
    this->Refresh();
}


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

    wxInitAllImageHandlers();
    MainFrame* fMain = new MainFrame(NULL);
    SetTopWindow(fMain);
    fMain->Show();
    return true;
}
