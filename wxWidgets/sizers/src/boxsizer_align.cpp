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

class Align : public wxFrame
{
public:
    explicit Align(std::string_view title);
};

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};


wxIMPLEMENT_APP(MyApp);


Align::Align(std::string_view title)
    : wxFrame{nullptr, -1, title.data(), wxPoint{-1,-1}, wxSize{300,200}}
{
    wxPanel* panel{new wxPanel{this,-1}};

    wxBoxSizer* vbox{new wxBoxSizer{wxVERTICAL}};
    wxBoxSizer* hbox1{new wxBoxSizer{wxHORIZONTAL}};
    wxBoxSizer* hbox2{new wxBoxSizer{wxHORIZONTAL}};

    wxButton* ok{new wxButton{panel, -1, "OK"}};
    wxButton* cancel{new wxButton{panel, -1, "Cancel"}};

    hbox1->Add(new wxPanel{panel, -1});
    vbox->Add(hbox1, 1, wxEXPAND);

    hbox2->Add(ok);
    hbox2->Add(cancel);

    vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

    panel->SetSizer(vbox);

    Centre();
}


bool MyApp::OnInit()
{
    Align* widget = new Align{"Align"};
    widget->Show(true);
    return true;
}
