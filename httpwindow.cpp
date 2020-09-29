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
#include "wx/protocol/http.h"
#include "wx/stream.h"
#include "wx/sstream.h"

HttpTestWindow::HttpTestWindow(wxWindow *parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):wxSplitterWindow(parent, id, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE | wxCLIP_CHILDREN)
{
    m_panel_top = new wxPanel(this, wxID_ANY);
	m_panel_top->SetBackgroundColour(*wxRED);
    m_panel_bottom = new wxPanel(this, wxID_ANY);
	m_panel_bottom->SetBackgroundColour(*wxBLUE);

    m_host = new wxTextCtrl(m_panel_top, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 30));
    m_url = new wxTextCtrl(m_panel_top, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 30));
	m_url->SetValue(wxT("/"));
    m_method = new wxTextCtrl(m_panel_top, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 30));
    m_data = new wxTextCtrl(m_panel_top, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 100), wxTE_MULTILINE);
    m_result = new wxTextCtrl(m_panel_bottom, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(300, 30), wxTE_MULTILINE);

    m_sizer_top = new wxGridSizer(2, 5, 5);
    m_sizer_bottom = new wxBoxSizer(::wxVERTICAL);
    m_panel_top->SetSizer(m_sizer_top);
    m_panel_bottom->SetSizer(m_sizer_bottom);

    m_sizer_top->Add(
        new wxStaticText( m_panel_top, wxID_ANY, "host:" ),
        wxSizerFlags().Align(wxALIGN_LEFT).Border(wxALL & ~wxBOTTOM, 5));
    m_sizer_top->Add(m_host, 1, wxALIGN_TOP, 0);
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

	wxButton *commit = new wxButton(m_panel_top, wxID_ANY, "提交");
	commit->Bind(wxEVT_BUTTON, &HttpTestWindow::onCommit, this);

	wxButton *clear = new wxButton(m_panel_top, wxID_ANY, "清空结果");
	clear->Bind(wxEVT_BUTTON, &HttpTestWindow::onClear, this);
    m_sizer_top->Add(commit, 1, wxALIGN_CENTER_VERTICAL, 0);
    m_sizer_top->Add(clear, 1, wxALIGN_CENTER_VERTICAL, 0);

    m_sizer_bottom->Add(m_result, 1, wxEXPAND, 0);

	this->SplitHorizontally(m_panel_top, m_panel_bottom, 300);
}

HttpTestWindow::~HttpTestWindow()
{
}

void HttpTestWindow::onCommit(wxCommandEvent& ev)
{
	printf("commit down\n");
	wxString host = m_host->GetLineText(0);
	wxString url = m_url->GetLineText(0);
	wxString method = m_method->GetLineText(0);
	wxString data = m_data->GetLineText(0);
	m_result->SetDefaultStyle(wxTextAttr(*wxRED));

	m_result->AppendText(host);
	m_result->AppendText(wxT("\n"));
	m_result->AppendText(url);
	m_result->AppendText(wxT("\n"));
	m_result->AppendText(method);
	m_result->AppendText(wxT("\n"));
	m_result->AppendText(data);
	m_result->AppendText(wxT("\n"));

	if (host == "") 
	{
		m_result->AppendText("host is nil\n");
		return;
	} 

	wxHTTP http;
	http.SetMethod(method);
	if (data != "") 
	{
		http.SetPostText("application/json", data);
	} 

	bool ok = http.Connect(host);
	if (ok) 
	{
		wxInputStream *httpStream = http.GetInputStream(url);
		if (http.GetError() == wxPROTO_NOERR) {
			wxString res;
			wxStringOutputStream out_stream(&res);
			httpStream->Read(out_stream);
			// 显示返回码
			m_result->AppendText(wxString::FromDouble(http.GetResponse()));
			m_result->AppendText(res);
			//wxMessageBox(res);
		}
		else {
			wxMessageBox(wxT("http error"));
		}
		wxDELETE(httpStream);
		http.Close();
	}
	else 
	{
		printf("connect error");
	}
}

void HttpTestWindow::onClear(wxCommandEvent& ev)
{
	printf("clear down\n");
	m_result->SetValue(wxT(""));
}
