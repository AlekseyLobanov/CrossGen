#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <ctime>

#include <wx/wx.h>
#include <wx/wfstream.h>
#include <wx/textfile.h>
#include "wxgui.hpp"

#define wxID_PATH 1079
#define wxID_GENERATE 1080

const wxChar CELL_CLEAR = wxT('+');

MainFrame::MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: MainFrame::MainFrame
    label_1 = new wxStaticText(this, wxID_ANY, _("Путь к сетке:"));
    tPath = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnPath = new wxButton(this, wxID_PATH, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    tOutput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxTE_WORDWRAP);
    btnGenerate = new wxButton(this, wxID_GENERATE, _("Генерировать кроссворд"));

    set_properties();
    do_layout();
    // end wxGlade
}


void MainFrame::set_properties()
{
    // begin wxGlade: MainFrame::set_properties
    SetTitle(_("Генератор кроссвордов"));
    SetSize(wxSize(700, 500));
    SetMinSize(wxSize(600,340));
    // end wxGlade
}


void MainFrame::do_layout()
{
    // begin wxGlade: MainFrame::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    sizer_2->Add(label_1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    sizer_2->Add(tPath, 1, 0, 0);
    sizer_2->Add(btnPath, 0, 0, 0);
    sizer_1->Add(sizer_2, 0, wxEXPAND, 0);
    sizer_3->Add(tOutput, 1, wxEXPAND, 0);
    bPreview = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap);
    sizer_3->Add(bPreview, 0, 0, 0);
    sizer_1->Add(sizer_3, 1, wxEXPAND, 0);
    sizer_4->Add(0, 0, 1, 0, 0);
    sizer_4->Add(btnGenerate, 0, 0, 0);
    sizer_1->Add(sizer_4, 0, wxEXPAND, 0);
    SetSizer(sizer_1);
    Layout();
    // end wxGlade
}


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    // begin wxGlade: MainFrame::event_table
    EVT_BUTTON(wxID_PATH, MainFrame::OnbtnPathClick)
    EVT_BUTTON(wxID_GENERATE, MainFrame::OnbtnGenerateClick)
    // end wxGlade
END_EVENT_TABLE();



void readDict(wxString path, DictType &dict){
    wxTextFile f;
    f.Open(path);
    for ( wxString str = f.GetFirstLine(); !f.Eof(); str = f.GetNextLine() ) {
        wxString key,val;
        int del_ind = str.Index('-');
        key = str.Left(del_ind-1);
        val = str.Right(str.size() - del_ind - 2);
        dict[key] = val;
    }
    wxLogDebug(wxString::Format(wxT("Прочитан словарь размером %d записей"), 
      static_cast<int>(dict.size())));
    f.Close();
};

void readGrid(wxString path, GridType &grid){
    wxTextFile f;
    f.Open(path);
    wxString str = f.GetFirstLine();
    
    grid.resize(str.size());
    for (unsigned int i = 0; i < grid.size(); ++i)
        grid.at(i).resize(f.GetLineCount());
        
    wxLogDebug(wxT("Total lines: %d. First line is %s and size = %d"),f.GetLineCount(), str.c_str(),str.size());
    unsigned int i = 0;
    for ( ; !f.Eof(); str = f.GetNextLine() ) {
        wxLogDebug(str);
        for (unsigned int j = 0; j < str.size(); ++j)
            grid.at(j).at(i) = str.at(j);
        i++;
    }
    wxLogDebug(wxT("Прочитана сетка размером %d x %d"), 
      static_cast<int>(grid.size()), static_cast<int>(grid.at(0).size()));
    f.Close();
}

void generateWordInfo(GridType &grid, std::vector<WordInfo> &winfos){
    wxLogDebug(wxT("Printing grid: "));
    for (size_t i = 0; i < grid.size(); ++i){
        wxString st;
        for (size_t j = 0; j < grid.at(0).size(); ++j)
            st+= grid.at(i).at(j);
        wxLogDebug(st);
    }
    size_t cur_ind = 1;
    bool exist = false;
    for (size_t i = 0; i < grid.size(); ++i){
        for (size_t j = 0; j < grid.at(0).size(); ++j){
            if (grid.at(i).at(j) == CELL_CLEAR){
                if (((j ==0) ||  (grid.at(i).at(j - 1) != CELL_CLEAR)) &&
                        (j != grid.at(0).size() - 1))
                    if (grid.at(i).at(j+1) == CELL_CLEAR){
                        size_t cur_len = 1;
                        bool cont = true;
                        while ((j + cur_len < grid.at(0).size()) && cont){
                            cur_len++;
                            if (grid.at(i).at(j+cur_len-1) != CELL_CLEAR){
                                cont = false;
                                cur_len--;
                            }
                        }
                        exist = true;
                        WordInfo t;
                        t.x      = i;
                        t.y      = j;
                        t.len    = cur_len;
                        t.ind    = cur_ind;
                        t.direct = false;
                        winfos.push_back(t);
                    }
                
                if (((i ==0) ||  (grid.at(i - 1).at(j) != CELL_CLEAR)) &&
                        (i != grid.size() - 1))
                    if (grid.at(i + 1).at(j) == CELL_CLEAR){
                        size_t cur_len = 1;
                        bool cont = true;
                        while ((i + cur_len < grid.size()) && cont){
                            cur_len++;
                            if (grid.at(i+cur_len-1).at(j) != CELL_CLEAR){
                                cont = false;
                                cur_len--;
                            }
                        }
                        exist = true;
                        WordInfo t;
                        t.x      = i;
                        t.y      = j;
                        t.len    = cur_len;
                        t.ind    = cur_ind;
                        t.direct = true;
                        winfos.push_back(t);
                    }
                if (exist){
                    exist = false;
                    cur_ind++;
                }
            }
        }
    }
}

bool procCross(UsedWords used, AllWordsType &words, CurGridType grid, 
        std::vector<WordInfo> &winfos, size_t cur_word_ind, std::vector<wxString> &out){
    if (cur_word_ind == winfos.size())
        return true;
    WordInfo cur_wi = winfos.at(cur_word_ind);
    size_t rand_add = rand() % 100000;
    size_t cur_len = cur_wi.len;
    size_t cur_words_size = words.at(cur_len).size();
    for (size_t i = 0; i < cur_words_size; ++i){
        wxString cur_word = words.at(cur_len).at((i + rand_add) % cur_words_size);
        if (used.find(cur_word) != used.end())
            continue;
        // Показывает, можно ли записать это слово в сетку
        bool can_write = true;
        if (cur_wi.direct == false){
            for (size_t j = 0; j < cur_wi.len; ++j)
                if ((grid.at(cur_wi.x).at(j + cur_wi.y) != CELL_CLEAR) &&
                    (grid.at(cur_wi.x).at(j + cur_wi.y) != cur_word.at(j)))
                    can_write = false;
        }
        
        if (cur_wi.direct == true){
            for (size_t j = 0; j < cur_wi.len; ++j)
                if ((grid.at(cur_wi.x + j).at(cur_wi.y) != CELL_CLEAR) &&
                   (grid.at(cur_wi.x + j).at(cur_wi.y) != cur_word.at(j)))
                    can_write = false;
        }
        
        if (can_write) {
            UsedWords t_used(used);
            t_used.insert(cur_word);
            
            CurGridType t_grid(grid);
            
            if (cur_wi.direct == false){
                for (size_t j = 0; j < cur_wi.len; ++j)
                    t_grid.at(cur_wi.x).at(j + cur_wi.y) = cur_word.at(j);
            }
            
            if (cur_wi.direct == true){
                for (size_t j = 0; j < cur_wi.len; ++j)
                    t_grid.at(cur_wi.x + j).at(cur_wi.y) = cur_word.at(j);
            }
                
            if (procCross(t_used, words, t_grid, winfos, cur_word_ind + 1, out)){
                //wxLogDebug(wxT("Word at (%d,%d) with len = %d and index = %d and dir = %d and word is ") + cur_word,
        //  cur_wi.x,cur_wi.y,cur_wi.len, cur_wi.ind, int(cur_wi.direct));
                wxLogDebug(cur_word);
                out.push_back(cur_word);
                return true;
            }
        }
    }
    return false;
}

void generateCross(GridType &grid, DictType &dict, std::vector<wxString> &words_out){
    AllWordsType words;
    for (DictType::iterator i = dict.begin(); i != dict.end(); ++i){
        if (words.size() <= i->first.size())
            words.resize(i->first.size() + 4);
        words.at(i->first.size()).push_back(i->first);
    }
    for (size_t i = 2; i < words.size(); ++i){
        wxLogDebug(wxT("Number of words with length %d is %d"), i, words.at(i).size());
    }
    std::vector<WordInfo> winfos;
    generateWordInfo(grid, winfos);
    for (size_t i = 0; i < winfos.size(); ++i)
        wxLogDebug(wxT("Word at (%d,%d) with len = %d and index = %d and dir = %d"),
          winfos.at(i).x,winfos.at(i).y,winfos.at(i).len, winfos.at(i).ind, int(winfos.at(i).direct));
    
    UsedWords t_used;
    srand(time(NULL));
    procCross(t_used, words, grid, winfos, 0, words_out);
    std::reverse(words_out.begin(), words_out.end());
}

void MainFrame::OnbtnPathClick(wxCommandEvent &event) {
    event.Skip();
    wxFileDialog dlgOpen(this, wxT("Open XYZ file"), wxEmptyString, wxEmptyString,
    wxT("Файлы кроссворда (*.cross)|*.cross"), wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    
    if (dlgOpen.ShowModal() == wxID_CANCEL)
        return;
    // proceed loading the file chosen by the user;
    // this can be done with e.g. wxWidgets input streams:
    wxFileInputStream input_stream(dlgOpen.GetPath());
    if (!input_stream.IsOk()) {
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
    
    for (size_t i = 0; i < winfos.size(); ++i){
        dc.DrawText(wxString::Format(wxT("%d"),winfos.at(i).ind), sq_w*winfos.at(i).x, sq_h*winfos.at(i).y);
    }
    
    if (_words.size() > 0) {
        cur_f = dc.GetFont();
        cur_f.SetPointSize(sq_h*0.6);
        dc.SetFont(cur_f);
        for (size_t i = 0; i < winfos.size(); ++i){
            if (winfos.at(i).direct == true){
                for (size_t j = 0; j < winfos.at(i).len; ++j)
                    dc.DrawText(_words.at(i).at(j),sq_w*(winfos.at(i).x+j)+sq_w*0.24, sq_h*winfos.at(i).y);
            } else {
                for (size_t j = 0; j < winfos.at(i).len; ++j)
                    dc.DrawText(_words.at(i).at(j),sq_w*winfos.at(i).x+sq_w*0.24, sq_h*(winfos.at(i).y+j));
            }
            
        }
    }
    
    bPreview->SetBitmap(bmp);
    
    dc.SelectObject( wxNullBitmap );
    
    this->Refresh();
}

void MainFrame::OnbtnGenerateClick(wxCommandEvent &event) {
    event.Skip();
    DictType dict;
    std::vector<wxString> words_out;
    readDict(wxT("fdict.txt"), dict);
    GridType grid;
    if (tPath->GetValue() == wxEmptyString){
        wxMessageBox( wxT("Не указана путь к сетке"), wxT("Инфо"), wxICON_INFORMATION);
        return;
    }
    readGrid(tPath->GetValue(), grid);
    try{
        generateCross(grid,dict,words_out);
        
        _words.clear();
        _words = words_out;
        
        std::vector<WordInfo> winfos;
        generateWordInfo(grid, winfos);
        
        tOutput->Clear();
        
        tOutput->AppendText(wxT("По вертикали:\n"));
        
        for (size_t i = 0; i < words_out.size(); ++i){
            if (winfos.at(i).direct == false)
                tOutput->AppendText(wxString::Format(wxT("%d. "), winfos.at(i).ind) 
                  + dict[words_out.at(i)] +wxT("\n"));
        }
        
        tOutput->AppendText(wxT("По горизонтали:\n"));
        
        for (size_t i = 0; i < words_out.size(); ++i){
            if (winfos.at(i).direct == true)
                tOutput->AppendText(wxString::Format(wxT("%d. "), winfos.at(i).ind) 
                  + dict[words_out.at(i)]+wxT("\n"));
        }
        if (winfos.size() == 0) 
            throw 42;
        SetGridImage(grid);
        _words.clear();
    }
    catch (...){
        tOutput->Clear();
        this->Refresh();
        wxMessageBox( wxT("Не могу создать кроссворд"), wxT("Ошибка"), wxICON_ERROR);
    }
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
    MainFrame* fMain = new MainFrame(NULL, wxID_ANY, wxEmptyString);
    SetTopWindow(fMain);
    fMain->Show();
    return true;
}
