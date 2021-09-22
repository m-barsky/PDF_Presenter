#include "editor_controller.h"

#include <string>

#include <wx/wx.h>
#include <wx/filedlg.h>

editor_controller::editor_controller() : m_document(), m_main_frame() {

}

void editor_controller::start() {
    m_main_frame = new MainFrame();
    m_main_frame->Show(true);

    if (!m_document.is_open()) {
        show_document_chooser();
    }
}

void editor_controller::show_document_chooser() {
    wxFileDialog file_dialog (m_main_frame, "Open PDF file", "", "", "PDF files (*.pdf;*.PDF)|*.pdf;*.PDF|All files (*)|*", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxSTAY_ON_TOP);
    
    if (file_dialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    m_document = std::move(document(static_cast<std::string>(file_dialog.GetPath())));
    m_main_frame->SetStatusText("File: " + static_cast<std::string>(m_document.name()));
}

