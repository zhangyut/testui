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

// For compilers that support precompilation, includes "wx/wx.h".
#include "httpwindow.h"

HttpTestWindow::HttpTestWindow(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):wxSplitterWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE | wxCLIP_CHILDREN)
{
    m_panel_top = new wxPanel(this, wxID_ANY);
	m_panel_top->SetBackgroundColour(*wxRED);
    m_panel_bottom = new wxPanel(this, wxID_ANY);
	m_panel_bottom->SetBackgroundColour(*wxBLUE);

    m_url = new wxTextCtrl(m_panel_top, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 30));
    m_method = new wxTextCtrl(m_panel_top, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 30));
    m_data = new wxTextCtrl(m_panel_top, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 100), wxTE_MULTILINE);
    m_result = new wxTextCtrl(m_panel_bottom, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 30));

    m_sizer_top = new wxGridSizer(2, 5, 5);
    m_sizer_bottom = new wxBoxSizer(::wxVERTICAL);
    m_panel_top->SetSizer(m_sizer_top);
    m_panel_bottom->SetSizer(m_sizer_bottom);

    m_sizer_top->Add(
        new wxStaticText( m_panel_top, wxID_ANY, "url:" ),
        wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL & ~wxBOTTOM, 5));
    m_sizer_top->Add(m_url, 1, wxALIGN_TOP, 0);
    m_sizer_top->Add(
        new wxStaticText( m_panel_top, wxID_ANY, "method:" ),
        wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL & ~wxBOTTOM, 5));
    m_sizer_top->Add(m_method, 1,wxALIGN_TOP, 0);
    m_sizer_top->Add(
        new wxStaticText( m_panel_top, wxID_ANY, "data:" ),
        wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL & ~wxBOTTOM, 5));
    m_sizer_top->Add(m_data, 1, wxALIGN_TOP, 0);
	wxButton *button = new wxButton(m_panel_top, wxID_ANY, "提交");
	button->Bind(wxEVT_BUTTON, &HttpTestWindow::onCommit, this);
    m_sizer_top->Add(button, 1, wxALIGN_CENTER_VERTICAL, 0);
    m_sizer_bottom->Add(m_result, 1, wxEXPAND, 0);

	this->SplitHorizontally(m_panel_top, m_panel_bottom, 300);
}

HttpTestWindow::~HttpTestWindow()
{
}

void HttpTestWindow::onCommit(wxCommandEvent& ev)
{
	printf("buttom down\n");
}

