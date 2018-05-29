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

class FlexGridSizer : public wxFrame
{
public:
    explicit FlexGridSizer(std::string_view title);

};

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};


wxIMPLEMENT_APP(MyApp);


FlexGridSizer::FlexGridSizer(std::string_view title)
    : wxFrame{nullptr, wxID_ANY, title.data(), wxPoint(-1,-1), wxSize{270,220}}
{
    wxPanel* panel{new wxPanel{this,-1}};
    wxBoxSizer* hbox{new wxBoxSizer{wxHORIZONTAL}};
    wxFlexGridSizer* fgs{new wxFlexGridSizer{3, 2, 9, 25}};

    wxStaticText* thetitle{new wxStaticText{panel, -1, "Title"}};
    wxStaticText* author{new wxStaticText{panel, -1 "Author"}};
    wxStaticText* review{new wxStaticText{panel, -1, "Review"}};

    wxTextCtrl* tc1{new wxTextCtrl{panel, -1,}};
    wxTextCtrl* tc2{new wxTextCtrl{panel, -1,}};
    wxTextCtrl* tc3{new wxTextCtrl{panel, -1, ""
                   ,wxPoint{-1,-1},wxSize{-1,-1}, wxTE_MULTILINE}};

    

bool MyApp::OnInit()
{
    FlexGridSizer* widget = new FlexGridSizer{"FlexGridSizer"};
    widget->Show(true);
    return true;
}
