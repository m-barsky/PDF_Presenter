#include "EditorController.h"

#include <string>

#include <wx/wx.h>
#include <wx/filedlg.h>

EditorController::EditorController() : m_document(), m_main_frame() {

}

void EditorController::start() {
    m_main_frame = new MainFrame();
    m_main_frame->Show(true);

    if (!m_document.is_open()) {
        show_document_chooser();
    }
}

void EditorController::show_document_chooser() {
    wxFileDialog file_dialog (m_main_frame, "Open PDF file", "", "", "PDF files (*.pdf;*.PDF)|*.pdf;*.PDF|All files (*)|*", wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxSTAY_ON_TOP);
    
    if (file_dialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    m_document = std::move(Document(static_cast<std::string>(file_dialog.GetPath())));
    m_main_frame->SetStatusText("File: " + static_cast<std::string>(m_document.name()));
}

