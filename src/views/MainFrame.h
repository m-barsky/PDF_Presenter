#pragma once

#include <string>

#include <wx/wx.h>
#include <wx/file.h>

#include "Document.h"

class MainFrame : public wxFrame {
public:
    MainFrame();
    virtual~MainFrame() = default;
    
    void ChoosePdfFile();

private:
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnOpenButton(wxCommandEvent& event);

    bool m_dirty;
    Document m_document;
};

