#ifndef CROSSGEN_HPP
#define CROSSGEN_HPP

#include <set>
#include <vector>
#include <map>
#include <algorithm>

#include <wx/wx.h>
#include <wx/textfile.h>

#include "crossbasetypes.hpp"

const wxChar CELL_CLEAR = wxT('+');
const uint32_t MAX_WORD_COUNT = 262144; // =2^18

void readDict(const wxString path, DictType &dict){
    wxTextFile f;
    f.Open(path);
    for ( wxString str = f.GetFirstLine(); !f.Eof(); str = f.GetNextLine() ) {
        wxString key,val;
        int del_ind = str.Index('-');
        key = str.Left(del_ind-1);
        val = str.Right(str.size() - del_ind - 2);
        dict[key] = val;
    }
    f.Close();
};

void readGrid(const wxString path, GridType &grid){
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
        ++i;
    }
    wxLogDebug(wxT("Прочитана сетка размером %d x %d"), 
      static_cast<int>(grid.size()), static_cast<int>(grid.at(0).size()));
    f.Close();
}

void generateWordInfo(const GridType &grid, std::vector<WordInfo> &winfos){
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
                        bool cont = true;
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
                        winfos.push_back(t);
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
                        winfos.push_back(t);
                    }
                if ( exist ){
                    exist = false;
                    ++cur_ind;
                }
            }
        }
    }
}

template <class T>
uint32_t getWordUniq(const T w_ind, const T w_len){
    return w_ind + w_len * MAX_WORD_COUNT;
}

bool procCross(UsedWords used, AllWordsType &words, CurGridType grid, 
        std::vector<WordInfo> &winfos, size_t cur_word_ind, std::vector<wxString> &out){
    if (cur_word_ind == winfos.size())
        return true;
    WordInfo cur_wi = winfos.at(cur_word_ind);
    size_t rand_add = rand() % 100000;
    size_t cur_len = cur_wi.len;
    size_t cur_words_size = words.at(cur_len).size();
    for (size_t icw = 0; icw < cur_words_size; ++icw){
        if (used.find(getWordUniq(icw,cur_len)) != used.end())
            continue;
        wxString cur_word = words.at(cur_len).at((icw + rand_add) % cur_words_size);
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
            t_used.insert(getWordUniq(icw,cur_len));
            
            CurGridType t_grid(grid);
            
            if ( cur_wi.direct ){
                for (size_t j = 0; j < cur_wi.len; ++j)
                    t_grid.at(cur_wi.x + j).at(cur_wi.y) = cur_word.at(j);
            } else {
                for (size_t j = 0; j < cur_wi.len; ++j)
                    t_grid.at(cur_wi.x).at(j + cur_wi.y) = cur_word.at(j);
            }
                
            if (procCross(t_used, words, t_grid, winfos, cur_word_ind + 1, out)){
                out.push_back(cur_word);
                return true;
            }
        }
    }
    return false;
}

void generateCross(GridType &grid, const DictType &dict, std::vector<wxString> &words_out){
    AllWordsType words;
    for (auto it = dict.begin(); it != dict.end(); ++it){
        if (words.size() <= it->first.size())
            words.resize(it->first.size() + 2);
        words.at(it->first.size()).push_back(it->first);
    }
    std::vector<WordInfo> winfos;
    generateWordInfo(grid, winfos);
    for (size_t i = 0; i < winfos.size(); ++i)
        wxLogDebug(wxT("Word at (%d,%d) with len = %d and index = %d and dir = %d"),
          winfos.at(i).x,winfos.at(i).y,winfos.at(i).len, winfos.at(i).ind, int(winfos.at(i).direct));
    
    UsedWords t_used;
    procCross(t_used, words, grid, winfos, 0, words_out);
    std::reverse(words_out.begin(), words_out.end());
}

#endif // CROSSGEN_HPP
