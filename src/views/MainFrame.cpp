#include "MainFrame.h"

#include <utility>

#include <wx/sizer.h>
#include <wx/filedlg.h>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "PDF Presenter"), m_image_panel() {
    auto file_menu = new wxMenu();
    // TODO: add open, save, save as, close
    file_menu->Append(wxID_OPEN, "&Open\tCTRL+O", "Open a new PDF document");
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT);

    auto help_menu = new wxMenu();
    help_menu->Append(wxID_ABOUT);

    auto menu_bar = new wxMenuBar();
    // transfer ownership
    menu_bar->Append(file_menu, "&File");
    menu_bar->Append(help_menu, "&Help");
    SetMenuBar(menu_bar);

    CreateStatusBar();
    SetStatusText("No file open");

    m_image_panel = new wxResizableImagePanel(this, 400, 400);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_image_panel, 1, wxEXPAND, 0);

    SetSizer(sizer);
}

void MainFrame::SetImage(wxImage image) {
    m_image_panel->SetImage(std::move(image));
}

