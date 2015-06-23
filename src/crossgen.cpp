#include "crossgen.hpp"


const wxChar      CELL_CLEAR     = wxT('+');
const wxChar      CELL_BORDER    = wxT('-');
const TransedChar TRANS_CLEAR    = 0;
const TransedChar TRANS_BORDER   = 1;
const uint32_t    MAX_WORD_COUNT = 262144; // =2^18

void readDict(const wxString &path, DictType &dict_out){
    wxTextFile f;
    f.Open(path);
    for (wxString str = f.GetFirstLine(); !f.Eof(); str = f.GetNextLine()) {
        int del_ind = str.Index('-');
        wxString key = str.Left(del_ind-1);
        wxString val = str.Right(str.size() - del_ind - 2);
        dict_out[key] = val;
    }
    f.Close();
};

void readGrid(const wxString &path, GridType &grid){
    wxTextFile f;
    f.Open(path);
    wxString str = f.GetFirstLine();
    
    grid.resize(str.size());
    for (unsigned int i = 0; i < grid.size(); ++i)
        grid.at(i).resize(f.GetLineCount());
        
    wxLogDebug(wxT("Total lines: %d. First line is %s and size = %d"),f.GetLineCount(), str.c_str(),str.size());
    for (unsigned int i = 0; !f.Eof(); str = f.GetNextLine()){
        wxLogDebug(str);
        for (unsigned int j = 0; j < str.size(); ++j)
            grid.at(j).at(i) = str.at(j);
        ++i;
    }

    wxLogDebug(wxT("Прочитана сетка размером %d x %d"), 
      static_cast<int>(grid.size()), static_cast<int>(grid.at(0).size()));
    f.Close();
}

wxString getFromTransed(const TransedWord &tw, const BackedCharsTransType &bchar_trans){
    wxString s;
    s.resize(tw.size());
    for (size_t i = 0; i < tw.size(); ++i){
        s[i] = bchar_trans.at(tw.at(i));
    }
    return s;
}

BackedCharsTransType getFromCharsTransed(const CharsTransType &char_trans){
    BackedCharsTransType t;
    for (auto it = char_trans.begin(); it != char_trans.end(); ++it)
        t[it->second] = it->first;
    return t;
}

void toWorkGridType(const GridType &grid, WorkGridType &grid_out){
    grid_out.resize(grid.size());
    for (size_t i = 0; i < grid.size(); ++i){
        grid_out.at(i).resize(grid.at(0).size());
        for (size_t j = 0; j < grid.at(0).size(); ++j){
            if ( grid.at(i).at(j) == CELL_CLEAR ) 
                grid_out.at(i).at(j) = TRANS_CLEAR;
            else
                grid_out.at(i).at(j) = TRANS_BORDER;
        }
    }
}

void generateAllWords(const DictType &dict, AllWordsType &words_out, 
        CharsTransType &char_trans_out){
    words_out.clear();
    char_trans_out.clear();
    char_trans_out[CELL_CLEAR]  = TRANS_CLEAR;
    char_trans_out[CELL_BORDER] = TRANS_BORDER;
    static_assert(TRANS_CLEAR + 1 == TRANS_BORDER, "TRANS_CLEAR + 1 != TRANS_BORDER");
    TransedChar st = TRANS_BORDER + 1;
    for (auto it = dict.begin(); it != dict.end(); ++it){
        if ( words_out.size() <= it->first.size() )
            words_out.resize(it->first.size() + 1);
        TransedWord t_tw(it->first.size());
        for (size_t i = 0; i < it->first.size(); ++i){
            auto cur_ch = it->first.at(i);
            if ( char_trans_out.find(cur_ch) == char_trans_out.end() ){
                char_trans_out[cur_ch] = st;
                ++st;
            }
            t_tw.at(i) = char_trans_out[cur_ch];
        }
        words_out.at(it->first.size()).push_back(t_tw);
    }
}

void generateWordInfo(const GridType &grid, std::vector<WordInfo> &winfos_out){
    wxLogDebug(wxT("Printing grid: "));
    for (size_t i = 0; i < grid.size(); ++i){
        wxString st;
        for (size_t j = 0; j < grid.at(0).size(); ++j)
            st += grid.at(i).at(j);
        wxLogDebug(st);
    }
    size_t cur_ind = 1;
    bool exist = false;
    auto y_len = grid.at(0).size();
    auto x_len = grid.size();
    for (size_t j = 0; j < y_len; ++j){
        for (size_t i = 0; i < x_len; ++i){
            if ( grid.at(i).at(j) == CELL_CLEAR ) {
                if ( ((j == 0) ||  (grid.at(i).at(j - 1) != CELL_CLEAR)) &&
                        (j !=y_len - 1) )
                    if ( grid.at(i).at(j+1) == CELL_CLEAR ) {
                        size_t cur_len = 1;
                        bool   cont    = true;
                        while ( (j + cur_len < y_len) && cont ) {
                            ++cur_len;
                            if ( grid.at(i).at(j+cur_len-1) != CELL_CLEAR ) {
                                cont = false;
                                --cur_len;
                            }
                        }
                        exist    = true;
                        
                        WordInfo t;
                        t.x      = i;
                        t.y      = j;
                        t.len    = cur_len;
                        t.ind    = cur_ind;
                        t.direct = false;
                        winfos_out.push_back(t);
                    }
                
                if ( ((i ==0) ||  (grid.at(i - 1).at(j) != CELL_CLEAR)) &&
                        (i != x_len - 1) )
                    if ( grid.at(i + 1).at(j) == CELL_CLEAR ){
                        size_t cur_len = 1;
                        bool cont = true;
                        while ((i + cur_len < x_len) && cont){
                            ++cur_len;
                            if (grid.at(i+cur_len-1).at(j) != CELL_CLEAR){
                                cont = false;
                                --cur_len;
                            }
                        }
                        exist    = true;
                        WordInfo t;
                        t.x      = i;
                        t.y      = j;
                        t.len    = cur_len;
                        t.ind    = cur_ind;
                        t.direct = true;
                        winfos_out.push_back(t);
                    }
                if ( exist ){
                    exist = false;
                    ++cur_ind;
                }
            }
        }
    }
}

bool procCross(
        UsedWords used,
        const AllWordsType &words,
        WorkGridType grid, 
        const std::vector<WordInfo> &winfos,
        const size_t cur_word_ind,
        std::vector<TransedWord> &out
){
    if ( cur_word_ind == winfos.size() )
        return true;
    WordInfo cur_wi = winfos.at(cur_word_ind);
    size_t rand_add = rand() % 100000;
    size_t cur_len  = cur_wi.len;
    size_t cur_words_size = words[cur_len].size();
    for (size_t icw = 0; icw < cur_words_size; ++icw){
        if ( used.find(getWordUniq(icw,cur_len)) != used.end() )
            continue;
        TransedWord cur_word = words[cur_len][(icw + rand_add) % cur_words_size];
        // Показывает, можно ли записать это слово в сетку
        bool can_write = true;
        if ( cur_wi.direct ){
            for (size_t j = 0; j < cur_wi.len; ++j)
                if ( (grid[cur_wi.x + j][cur_wi.y] != TRANS_CLEAR) &&
                   (grid[cur_wi.x + j][cur_wi.y] != cur_word[j]) )
                    can_write = false;
        } else {
            for (size_t j = 0; j < cur_wi.len; ++j)
                if ( (grid[cur_wi.x][j + cur_wi.y] != TRANS_CLEAR) &&
                    (grid[cur_wi.x][j + cur_wi.y] != cur_word[j]) )
                    can_write = false;
        }
        
        if ( can_write ) {
            UsedWords t_used(used);
            t_used.insert(getWordUniq(icw,cur_len));
            
            WorkGridType t_grid(grid);
            
            if ( cur_wi.direct ){
                for (size_t j = 0; j < cur_wi.len; ++j)
                    t_grid[cur_wi.x + j][cur_wi.y] = cur_word[j];
            } else {
                for (size_t j = 0; j < cur_wi.len; ++j)
                    t_grid[cur_wi.x][j + cur_wi.y] = cur_word[j];
            }
                
            if (procCross(t_used, words, t_grid, winfos, cur_word_ind + 1, out)){
                out.push_back(cur_word);
                return true;
            }
        }
    }
    return false;
}

void generateCross(const GridType &grid, const AllWordsType &words, 
    const CharsTransType &trans_type, std::vector<wxString> &words_out){
    
    std::vector<WordInfo> winfos;
    generateWordInfo(grid, winfos);
    for (size_t i = 0; i < winfos.size(); ++i)
        wxLogDebug(wxT("Word at (%d,%d) with len = %d and index = %d and dir = %d"),
          winfos.at(i).x,winfos.at(i).y,winfos.at(i).len, winfos.at(i).ind, int(winfos.at(i).direct));
          
    WorkGridType grid_work;
    toWorkGridType(grid, grid_work);
    UsedWords t_used;
    std::vector< TransedWord > words_trans_out;
    procCross(t_used, words, grid_work, winfos, 0, words_trans_out);
    std::reverse(words_trans_out.begin(), words_trans_out.end());
    BackedCharsTransType bctt = getFromCharsTransed(trans_type);
    words_out.resize(words_trans_out.size());
    std::transform(
        words_trans_out.begin(),
        words_trans_out.end(),
        words_out.begin(), [bctt](const TransedWord &tw){
            return getFromTransed(tw, bctt);
        }
    );
}
