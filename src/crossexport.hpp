#ifndef CROSSEXPORT_HPP
#define CROSSEXPORT_HPP

#include <wx/wx.h>
#include <wx/textfile.h>

#include "crossgen.hpp"
#include "crossbasetypes.hpp"

void fillCross(FilledCrossword &cross);

wxString getGridString(const FilledCrossword &cross, wxChar space);

wxString getQuesString(const FilledCrossword &cross);

void exportToString(const FilledCrossword &cross, wxString &str_out, wxChar space);

bool exportToFile(const FilledCrossword &cross, const wxString path);

#endif // CROSSEXPORT_HPP
