#ifndef CROSSBASETYPES_HPP
#define CROSSBASETYPES_HPP

#include <set>
#include <vector>
#include <cstdint>

typedef std::map<wxString,wxString> DictType;
typedef std::vector< std::vector<wxChar> > GridType;
typedef std::vector< std::vector<wxChar> > CurGridType;
// Fisrt index is a word length
typedef std::vector< std::vector<wxString> > AllWordsType; 
typedef std::set< uint32_t > UsedWords;

struct WordInfo {
    size_t x;
    size_t y;
    size_t len;
    size_t ind;
    //true for vertical and false for horisontal
    bool direct;
};

#endif // CROSSBASETYPES_HPP
