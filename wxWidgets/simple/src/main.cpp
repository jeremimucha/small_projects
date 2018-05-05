#include <wx/wxprec.h>
#include <gsl/string_span>
#include <string_view>
using gsl::cstring_span;
using gsl::czstring;
using gsl::ensure_z;

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif


class Simple : public wxFrame
{
public:
    explicit Simple(std::string_view title);
    void OnQuit(wxCommandEvent&);
};

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};


wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit()
{
    // auto hello = gsl::ensure_z("Simple Hello");
    const char* title = "Simple Hello";
    Simple* frame = new Simple(title);
    frame->Show(true);
    return true;
}

Simple::Simple(std::string_view title)
    : wxFrame(nullptr, wxID_ANY, title.data(), wxDefaultPosition, wxSize(250,150))
{
    SetIcon(wxIcon(wxT("icon.xpm")));
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxButton* button = new wxButton(panel, wxID_EXIT, "Quit", wxPoint{20,20});
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED,
        wxCommandEventHandler(Simple::OnQuit));
    button->SetFocus();
    Centre();
}

void Simple::OnQuit(wxCommandEvent&)
{
    Close(true);
}