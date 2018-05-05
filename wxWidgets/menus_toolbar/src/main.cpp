#include <string_view>
#include <utility>
#include <iostream>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/menu.h>
#endif


struct SimpleMenu : public wxFrame
{
    explicit SimpleMenu(std::string_view title);

    void OnQuit(wxCommandEvent&);

    wxMenuBar* menubar;
    wxMenu* file;
    wxMenu* imp;
    wxMenuItem* quit;
    wxToolBar* toolbar1;
    wxToolBar* toolbar2;
};


class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

enum {ID_Plus = 101, ID_Minus = 102};


wxIMPLEMENT_APP(MyApp);


SimpleMenu::SimpleMenu(std::string_view title)
    : wxFrame{nullptr, wxID_ANY, title.data(), wxDefaultPosition, wxSize{280,180}}
    , menubar{new wxMenuBar}
    , file{new wxMenu}
    , imp{new wxMenu}
    , quit{new wxMenuItem{file, wxID_EXIT, "&Quit\tCtrl+W"}}
    , toolbar1{new wxToolBar{this, wxID_ANY}}
    , toolbar2{new wxToolBar{this, wxID_ANY}}
{
// --- fill a menu with items
    file->Append(wxID_ANY, "&New");
    file->Append(wxID_ANY, "&Open");
    file->Append(wxID_ANY, "&Save");
// --- a line separating logically different actions of a menu
    file->AppendSeparator();

// --- a submenu is just a regular menu, but appended to another menu
    imp->Append(wxID_ANY, "Import newsfeed...");
    imp->Append(wxID_ANY, "Import bookmarks...");
    imp->Append(wxID_ANY, "Import mail...");
    file->AppendSubMenu(imp, "I&mport");

// --- append an explicitly allocated menu item
    file->Append(quit);

// --- append a menu to a menubar
    menubar->Append(file, "&File");
    SetMenuBar(menubar);

// --- create a toolbar
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap exit{"exit.png", wxBITMAP_TYPE_PNG};
    wxBitmap newb{"new.png", wxBITMAP_TYPE_PNG};
    wxBitmap open{"open.png", wxBITMAP_TYPE_PNG};
    wxBitmap save{"save.png", wxBITMAP_TYPE_PNG};
// --- CreateToolBar() lets us have only a single toolbar
// --- We need to allocate the toolbars manually if more than one is needed
    // wxToolBar* toolbar = CreateToolBar();
    // toolbar->AddTool(wxID_EXIT, "Exit application", std::move(exit));
    // toolbar->Realize();
    wxBoxSizer* vbox{new wxBoxSizer{wxVERTICAL}};

    toolbar1->AddTool(wxID_ANY, "New", std::move(newb));
    toolbar1->AddTool(wxID_ANY, "Open", std::move(open));
    toolbar1->AddTool(wxID_ANY, "", std::move(save));
    toolbar1->Realize();

    toolbar2->AddTool(wxID_EXIT, "Exit Application", std::move(exit));
    toolbar2->Realize();
    vbox->Add(toolbar1, 0, wxEXPAND);
    vbox->Add(toolbar2, 0, wxEXPAND);

    SetSizer(vbox);

    Bind(wxEVT_MENU, &SimpleMenu::OnQuit, this, wxID_EXIT);
    // Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
    //     wxCommandEventHandler(SimpleMenu::OnQuit));
    Centre();
}

void SimpleMenu::OnQuit(wxCommandEvent&)
{
    std::cout << "Closing..." << std::endl;
    Close(true);
}


bool MyApp::OnInit()
{
    auto* menu = new SimpleMenu("Simple Menu");
    menu->Show(true);

    return true;
}
