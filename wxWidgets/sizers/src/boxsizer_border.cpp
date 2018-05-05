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

class Border : public wxFrame
{
public:
    explicit Border(std::string_view title);
};

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};


wxIMPLEMENT_APP(MyApp);


Border::Border(std::string_view title)
    : wxFrame{nullptr, wxID_ANY, title.data(), wxDefaultPosition, wxSize{600,400}}
{
    wxColour colour1, colour2, colour3, colour4;
    colour1.Set("#000000");
    colour2.Set("#ededed");
    colour3.Set("#00abcd");
    colour4.Set("#ff00ff");

    wxPanel* panel{new wxPanel{this,-1}};
    panel->SetBackgroundColour(colour1);
    wxBoxSizer* vbox{new wxBoxSizer{wxVERTICAL}};

    wxPanel* leftpanel{new wxPanel{panel, wxID_ANY}};
    leftpanel->SetBackgroundColour(colour3);
    vbox->Add(leftpanel, 0, wxALIGN_LEFT | wxEXPAND | wxALL, 20);
    wxPanel* midpanel{new wxPanel{panel, wxID_ANY}};
    midpanel->SetBackgroundColour(colour2);
    vbox->Add(midpanel, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 20);
    wxPanel* rightpanel{new wxPanel{panel, wxID_ANY}};
    rightpanel->SetBackgroundColour(colour4);
    vbox->Add(rightpanel, 2, wxALIGN_RIGHT | wxEXPAND | wxALL, 20);

    panel->SetSizer(vbox);

    Centre();
}


bool MyApp::OnInit()
{
    Border* widget = new Border{"Border"};
    widget->Show(true);
    return true;
}
