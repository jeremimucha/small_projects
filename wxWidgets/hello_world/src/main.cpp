#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnDongerino(wxCommandEvent& event);
};

enum { ID_Hello = 1, ID_Dongerino };

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenu* menuDongerino = new wxMenu;
    menuDongerino->Append(ID_Dongerino, "&Dongerino...\tCtrl-D",
                          "Dongerino status bar message");

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    menuBar->Append(menuDongerino, "&Dongerino");

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnDongerino, this, ID_Dongerino);
}

void MyFrame::OnExit(wxCommandEvent&)
{
    Close(true);
}
void MyFrame::OnAbout(wxCommandEvent&)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
void MyFrame::OnHello(wxCommandEvent&)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnDongerino(wxCommandEvent&)
{
    wxMessageBox("Dongerino", "Dongerino title?", wxOK);
}
