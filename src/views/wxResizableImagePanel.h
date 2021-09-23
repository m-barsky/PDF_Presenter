#pragma once

#include <wx/wx.h>

class wxResizableImagePanel : public wxPanel {
public:
    wxResizableImagePanel(wxFrame* parent);
    wxResizableImagePanel(wxFrame* parent, wxCoord width, wxCoord height);
    wxResizableImagePanel(wxFrame* parent, const wxString& filename, wxBitmapType format);
    wxResizableImagePanel(wxFrame* parent, wxImage image);
    virtual ~wxResizableImagePanel() = default;

    void OnPaint(wxPaintEvent& event);
    void Paint();
    void OnSize(wxSizeEvent& event);
    void Render(wxDC& dc);

    void SetImage(const wxImage& image);
    void SetImage(const wxString& filename, wxBitmapType format);

private:
    wxImage m_image;
    wxBitmap m_bitmap;
    wxCoord m_width;
    wxCoord m_height;

    DECLARE_EVENT_TABLE()
};

