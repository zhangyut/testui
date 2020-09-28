/////////////////////////////////////////////////////////////////////////////
// Name:        httpwindow.cpp
// Purpose:     testui sample
// Author:      zhanglei
// Modified by:
// Created:     09/28/20
// Copyright:   (c) hslearn
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#ifndef __HTTP_TEST_WINDOW__
#define __HTTP_TEST_WINDOW__
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/log.h"
#include "wx/image.h"
#include "wx/filedlg.h"
#include "wx/colordlg.h"
#include "wx/srchctrl.h"
#include "wx/splitter.h"

enum {
	ID_BUTTON_COMMIT = 1
};

class HttpTestWindow: public wxSplitterWindow
{
public:
    HttpTestWindow(wxWindow *parent,
            wxWindowID id = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE|wxCLIP_CHILDREN);
    virtual ~HttpTestWindow();

private:
	void onCommit(wxCommandEvent&);

private:
    wxTextCtrl         *m_textWindow;
    wxTextCtrl         *m_textWindow2;

    wxPanel            *m_panel_top;
    wxPanel            *m_panel_bottom;
    wxTextCtrl         *m_url;
    wxTextCtrl         *m_method;
    wxTextCtrl         *m_data;
    wxTextCtrl         *m_result;
    wxGridSizer        *m_sizer_top;
    wxBoxSizer         *m_sizer_bottom;
    
    //wxDECLARE_EVENT_TABLE();
};

#endif
