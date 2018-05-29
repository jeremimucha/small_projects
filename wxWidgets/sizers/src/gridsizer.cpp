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


// wxBoxSizer(int orient)
// wxSizerItem* Add( wxWindow* window   // the widged being added to the sizer
//                 , int proportion = 0 // how will resizing affect the widget
//                 , int flag = 0       // 
//                 , int border = 0
//                 )

class GridSizer : public wxFrame
{
public:
    explicit GridSizer(std::string_view title);

    wxMenuBar*   menubar;
    wxMenu*      file;

    wxBoxSizer*  sizer;
    wxGridSizer* gs;
    wxTextCtrl*  display;
};

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};


wxIMPLEMENT_APP(MyApp);


GridSizer::GridSizer(std::string_view title)
    : wxFrame{nullptr, wxID_ANY, title.data(), wxPoint(-1,-1), wxSize{270,220}}
    , menubar{new wxMenuBar}
    , file{new wxMenu}
    , sizer{new wxBoxSizer{wxVERTICAL}}
    , gs{new wxGridSizer{4,4,3,3}}
    , display{new wxTextCtrl{this, -1, "", wxPoint{-1,-1}, wxSize{-1,-1}, wxTE_RIGHT}}
{
    SetMenuBar(menubar);
    sizer->Add(display, 0, wxEXPAND | wxTOP | wxBOTTOM, 4);
    gs->Add(new wxButton{this, -1, "Cls"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "Bck"}, 0, wxEXPAND);
    gs->Add(new wxStaticText{this, -1, ""}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "Close"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "7"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "8"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "9"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "/"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "4"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "5"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "6"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "*"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "1"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "2"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "3"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "-"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "0"}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "."}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "="}, 0, wxEXPAND);
    gs->Add(new wxButton{this, -1, "+"}, 0, wxEXPAND);

    sizer->Add(gs, 1, wxEXPAND);
    SetSizer(sizer);
    SetMinSize(wxSize{270,220});

    Centre();
}


bool MyApp::OnInit()
{
    GridSizer* widget = new GridSizer{"GridSizer"};
    widget->Show(true);
    return true;
}
