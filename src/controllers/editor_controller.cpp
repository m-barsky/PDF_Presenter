#include "editor_controller.h"

#include <string>

#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/display.h>

#include "image_utils.h"

editor_controller::editor_controller() : m_document(), m_renderer(), m_main_frame() {

}

void editor_controller::start() {
    m_main_frame = new MainFrame();
    m_main_frame->Show(true);
    m_main_frame->Bind(wxEVT_MENU, &editor_controller::on_about, this, wxID_ABOUT);
    m_main_frame->Bind(wxEVT_MENU, &editor_controller::on_exit, this, wxID_EXIT);
    m_main_frame->Bind(wxEVT_MENU, &editor_controller::on_open, this, wxID_OPEN);
}

void editor_controller::show_document_chooser() {
    wxFileDialog file_dialog (m_main_frame, "Open PDF file", "", "", "PDF files (*.pdf;*.PDF)|*.pdf;*.PDF|All files (*)|*", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxSTAY_ON_TOP);
    
    if (file_dialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    m_document = std::move(document(static_cast<std::string>(file_dialog.GetPath())));
    m_main_frame->SetStatusText("File: " + static_cast<std::string>(m_document.name()));

    auto display_size = get_screen_size();
    auto rendered_image = m_renderer.render_page(m_document, 0, display_size.first, display_size.second);
    m_main_frame->SetImage(image_utils::image_to_wxImage(rendered_image));
}

void editor_controller::on_about([[maybe_unused]] wxCommandEvent& event) {
    wxMessageBox("PDF Presenter: version 0.0.1", "PDF Presenter", wxOK | wxICON_INFORMATION);
}

void editor_controller::on_exit([[maybe_unused]] wxCommandEvent& event) {
    if (m_document.dirty()) {
        // TODO: display are you sure: "save, don't save, cancel"
    }

    m_main_frame->Close();
}

void editor_controller::on_open([[maybe_unused]] wxCommandEvent& event) {
    show_document_chooser();
}

std::pair<int, int> editor_controller::get_screen_size() const {
    wxDisplay display {}; // create for default display (first display detected)
    auto rect = display.GetClientArea();

    return { rect.GetWidth(), rect.GetHeight() };
}

