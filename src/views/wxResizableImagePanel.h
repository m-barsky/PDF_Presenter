#pragma once

#include <wx/wx.h>

class wxResizableImagePanel : public wxPanel {
public:
    wxResizableImagePanel(wxFrame* parent, wxString filename, wxBitmapType format);
    wxResizableImagePanel(wxFrame* parent, wxImage image);

    void OnPaint(wxPaintEvent& event);
    void Paint();
    void OnSize(wxSizeEvent& event);
    void Render(wxDC& dc);

private:
    wxImage m_image;
    wxBitmap m_bitmap;
    wxCoord m_width;
    wxCoord m_height;

    DECLARE_EVENT_TABLE()
};

