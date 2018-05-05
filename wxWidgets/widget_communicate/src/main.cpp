#include <wx/wxprec.h>
#include <gsl/string_span>
#include <string_view>
using gsl::cstring_span;
using gsl::czstring;
using gsl::ensure_z;

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/panel.h>
    #include <wx/stattext.h>
#endif


class LeftPanel : public wxPanel
{
public:
    LeftPanel(wxPanel* parent);

    void OnPlus(wxCommandEvent&);
    void OnMinus(wxCommandEvent&);

    wxPanel*  m_parent;
    wxButton* m_plus;
    wxButton* m_minus;
    int count;
};

class RightPanel : public wxPanel
{
public:
    RightPanel(wxPanel* parent);

    void OnSetText(wxCommandEvent&);

    wxStaticText* m_text;

};

class Communicate : public wxFrame
{
public:
    Communicate(std::string_view title);

    wxPanel *m_parent;
    LeftPanel* m_lp;
    RightPanel* m_rp;
};

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

enum {ID_Plus = 101, ID_Minus = 102};

wxIMPLEMENT_APP(MyApp);


LeftPanel::LeftPanel(wxPanel* parent)
    : wxPanel(parent, -1, wxPoint{-1,-1}, wxSize(-1,-1), wxBORDER_SUNKEN)
    , m_parent{parent}
    , m_plus{new wxButton{this, ID_Plus, "+", wxPoint{10,10}}}
    , m_minus{new wxButton{this, ID_Minus, "-", wxPoint{10,60}}}
    , count{0}
{
    // m_plus = new wxButton{this, ID_Plus, "+", wxPoint{10,10}};
    // m_minus = new wxButton{this, ID_Minus, "-", wxPoint{10,60}};
    Connect(ID_Plus, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(LeftPanel::OnPlus));
    Connect(ID_Minus, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(LeftPanel::OnMinus));
}

void LeftPanel::OnPlus(wxCommandEvent&)
{
    ++count;
    Communicate* comm = static_cast<Communicate*>(m_parent->GetParent());
    comm->m_rp->m_text->SetLabel(wxString::Format("%d",count));
}

void LeftPanel::OnMinus(wxCommandEvent&)
{
    --count;
    Communicate* comm = static_cast<Communicate*>(m_parent->GetParent());
    comm->m_rp->m_text->SetLabel(wxString::Format("%d",count));
}

RightPanel::RightPanel(wxPanel* parent)
    : wxPanel{parent, wxID_ANY, wxDefaultPosition, wxSize{270,150}, wxBORDER_SUNKEN}
    , m_text{new wxStaticText{this, -1, "0", wxPoint{40,60}}}
{
    // m_text = new wxStaticText{this, -1, "0", wxPoint{40,60}};
}

Communicate::Communicate(std::string_view title)
    : wxFrame{nullptr, wxID_ANY, title.data(), wxDefaultPosition, wxSize{290,150}}
    , m_parent{new wxPanel{this, wxID_ANY}}
    , m_lp{new LeftPanel(m_parent)}
    , m_rp{new RightPanel(m_parent)}
{
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    hbox->Add(m_lp, 1, wxEXPAND | wxALL, 5);
    hbox->Add(m_rp, 1, wxEXPAND | wxALL, 5);
    m_parent->SetSizer(hbox);

    this->Centre();
}


bool MyApp::OnInit()
{
    Communicate* communicate = new Communicate("Widgets communicate");
    communicate->Show(true);

    return true;
}
