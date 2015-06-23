#ifndef CROSSGEN_HPP
#define CROSSGEN_HPP

#include <set>
#include <vector>
#include <map>
#include <algorithm>

#include <wx/wx.h>
#include <wx/textfile.h>

#include "crossbasetypes.hpp"

extern const wxChar      CELL_CLEAR     ;
extern const wxChar      CELL_BORDER    ;
extern const TransedChar TRANS_CLEAR    ;
extern const TransedChar TRANS_BORDER   ;
extern const uint32_t    MAX_WORD_COUNT ;

void readDict(const wxString &path, DictType &dict_out);

void readGrid(const wxString &path, GridType &grid);

wxString getFromTransed(const TransedWord &tw, const BackedCharsTransType &bchar_trans);

BackedCharsTransType getFromCharsTransed(const CharsTransType &char_trans);

void toWorkGridType(const GridType &grid, WorkGridType &grid_out);

void generateAllWords(const DictType &dict, AllWordsType &words_out, 
        CharsTransType &char_trans_out);

void generateWordInfo(const GridType &grid, std::vector<WordInfo> &winfos_out);

template <class T>
uint32_t getWordUniq(const T &w_ind, const T &w_len){
    return w_ind + w_len * MAX_WORD_COUNT;
}

bool procCross(
        UsedWords used,
        const AllWordsType &words,
        WorkGridType grid, 
        const std::vector<WordInfo> &winfos,
        const size_t cur_word_ind,
        std::vector<TransedWord> &out
);

void generateCross(const GridType &grid, const AllWordsType &words, 
    const CharsTransType &trans_type, std::vector<wxString> &words_out);

#endif // CROSSGEN_HPP
