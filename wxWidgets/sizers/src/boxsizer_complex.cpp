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
//                 , int flag = 0       // flags controlling the alignment and borders
//                 , int border = 0     // border size in pixels
//                 )

class GotoClass : public wxFrame
{
public:
    explicit GotoClass(std::string_view title);
};

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};


wxIMPLEMENT_APP(MyApp);


GotoClass::GotoClass(std::string_view title)
    : wxFrame{nullptr, -1, title.data(), wxPoint{-1,-1}, wxSize{450,400}}
{
    wxPanel* panel{new wxPanel{this,-1}};

    wxBoxSizer* vbox{new wxBoxSizer{wxVERTICAL}};
    
    wxBoxSizer* hbox1{new wxBoxSizer{wxHORIZONTAL}};
    wxStaticText* st1{new wxStaticText(panel, wxID_ANY, "Class name")};
    hbox1->Add(st1, 0, wxRIGHT, 8);
    wxTextCtrl* tc{new wxTextCtrl{panel, wxID_ANY}};
    hbox1->Add(tc, 1);
    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer* hbox2{new wxBoxSizer{wxHORIZONTAL}};
    wxStaticText* st2{new wxStaticText{panel, wxID_ANY, "Matching Classes"}};
    hbox2->Add(st2, 0);
    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer* hbox3{new wxBoxSizer{wxHORIZONTAL}};
    wxTextCtrl* tc2{new wxTextCtrl{panel, wxID_ANY, "",
                     wxPoint{-1,-1}, wxSize{-1,-1}, wxTE_MULTILINE}};
    hbox3->Add(tc2, 1, wxEXPAND);
    vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);

    vbox->Add(-1, 25);

    wxBoxSizer* hbox4{new wxBoxSizer{wxHORIZONTAL}};
    wxCheckBox* cb1{new wxCheckBox{panel, wxID_ANY, "Case Sensitive"}};
    hbox4->Add(cb1, wxLEFT, 10);
    wxCheckBox* cb2{new wxCheckBox{panel, wxID_ANY, "Nested Classes"}};
    hbox4->Add(cb2, wxLEFT, 10);
    wxCheckBox* cb3{new wxCheckBox{panel, wxID_ANY, "Non-project Classes"}};
    hbox4->Add(cb3, wxLEFT, 10);
    vbox->Add(hbox4, 0, wxLEFT, 10);

    vbox->Add(-1, 25);

    wxBoxSizer* hbox5{new wxBoxSizer{wxHORIZONTAL}};
    wxButton* btn1{new wxButton{panel, wxID_ANY, "OK"}};
    hbox5->Add(btn1, 0);
    wxButton* btn2{new wxButton{panel, wxID_ANY, "Cancel"}};
    hbox5->Add(btn2, 0, wxLEFT | wxBOTTOM, 5);
    vbox->Add(hbox5, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    panel->SetSizer(vbox);

    Centre();
}


bool MyApp::OnInit()
{
    GotoClass* widget = new GotoClass{"GotoClass"};
    widget->Show(true);
    return true;
}
