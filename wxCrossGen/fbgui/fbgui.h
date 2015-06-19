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
#include <wx/stattext.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_EXECUTE 1000
#define wxID_EXPORT 1001

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
		wxStaticBitmap* bPreview;
		wxTextCtrl* tOutput;
		
		wxButton* bGenerate;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onExitClick( wxCloseEvent& event ) { event.Skip(); }
		virtual void onOpenGridClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onGenerateClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onExportClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSettingsClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onExitClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onAboutClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		VMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("CrossGen"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,500 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~VMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class VSettingsDialog
///////////////////////////////////////////////////////////////////////////////
class VSettingsDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		
		wxTextCtrl* tDictPath;
		wxButton* bDictPath;
		
		
		wxButton* bCancel;
		wxButton* bOk;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onDictPathClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCancelClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOkClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		VSettingsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 425,120 ), long style = wxDEFAULT_DIALOG_STYLE );
		~VSettingsDialog();
	
};

#endif //__fbgui__
