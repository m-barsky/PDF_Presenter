#include "MainFrame.h"

#include <utility>

#include <wx/filedlg.h>

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "PDF Presenter") {
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

    Bind(wxEVT_MENU, &MainFrame::OnOpenButton, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
}

void MainFrame::OnAbout([[maybe_unused]] wxCommandEvent& event) {
    wxMessageBox("PDF Presenter: version 0.0.1", "PDF Presenter", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit([[maybe_unused]] wxCommandEvent& event) {
    Close(true);
}

void MainFrame::OnOpenButton([[maybe_unused]] wxCommandEvent& event) {
}

