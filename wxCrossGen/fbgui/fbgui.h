///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 29 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __fbgui__
#define __fbgui__

#include <wx/intl.h>

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class VMainFrame
///////////////////////////////////////////////////////////////////////////////
class VMainFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mMenu;
		wxMenu* miFile;
		wxMenu* miHelp;
		wxTextCtrl* tPath;
		wxButton* bPath;
		wxTextCtrl* tOutput;
		wxStaticBitmap* bPreview;
		
		wxButton* bGenerate;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onExitClick( wxCloseEvent& event ) { event.Skip(); }
		virtual void onOpenGridClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onGenerateClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onExitClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAboutClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		VMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("CrossGen"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~VMainFrame();
	
};

#endif //__fbgui__
