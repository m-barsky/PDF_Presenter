#pragma once

#include <wx/wx.h>

#include "wxResizableImagePanel.h"

class MainFrame : public wxFrame {
public:
    MainFrame();
    virtual ~MainFrame() = default;

    void SetImage(wxImage image);

private:
    wxResizableImagePanel* m_image_panel;
};

