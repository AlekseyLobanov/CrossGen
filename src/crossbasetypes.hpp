#ifndef CROSSBASETYPES_HPP
#define CROSSBASETYPES_HPP

#include <set>
#include <vector>
#include <cstdint>
#include <map>

typedef std::map< wxString, wxString > DictType;
typedef std::vector< std::vector< wxChar > > GridType;

typedef uint8_t TransedChar;
typedef std::vector< TransedChar > TransedWord;

typedef std::vector< std::vector< TransedChar > > WorkGridType;
typedef std::map< wxChar, TransedChar > CharsTransType;
typedef std::map< TransedChar, wxChar > BackedCharsTransType;
// Fisrt index is a word length
typedef std::vector< std::vector< TransedWord > > AllWordsType; 
typedef std::set< uint32_t > UsedWords;

struct WordInfo {
    size_t x;
    size_t y;
    size_t len;
    size_t ind;
    //true for vertical and false for horisontal
    bool direct;
};

struct FilledCrossword {
    GridType grid;
    std::vector< WordInfo > words;
    std::vector< wxString > ans;
};

#endif // CROSSBASETYPES_HPP
