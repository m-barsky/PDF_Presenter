#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
    MainFrame();
    virtual~MainFrame() = default;

private:
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnOpenButton(wxCommandEvent& event);
};

