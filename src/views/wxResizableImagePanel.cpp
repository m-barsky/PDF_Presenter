#include "wxResizableImagePanel.h"

wxResizableImagePanel::wxResizableImagePanel(wxFrame* parent) : wxPanel(parent), m_image(), m_bitmap(), m_width(-1), m_height(-1) {

}

wxResizableImagePanel::wxResizableImagePanel(wxFrame* parent, wxCoord width, wxCoord height) : wxPanel(parent), m_image(width, height, true), m_bitmap(), m_width(width), m_height(height) {

}

wxResizableImagePanel::wxResizableImagePanel(wxFrame* parent, const wxString& filename, wxBitmapType format) : wxPanel(parent), m_image(), m_bitmap(), m_width(m_image.GetWidth()), m_height(m_image.GetHeight()) {
    SetImage(filename, format);
}

wxResizableImagePanel::wxResizableImagePanel(wxFrame* parent, wxImage image) : wxPanel(parent), m_image(image), m_bitmap(), m_width(m_image.GetWidth()), m_height(m_image.GetHeight()) {

}

void wxResizableImagePanel::OnPaint([[maybe_unused]] wxPaintEvent& event) {
    wxPaintDC dc (this);
    Render(dc);
}

void wxResizableImagePanel::Paint() {
    wxClientDC dc (this);
    Render(dc);
}

void wxResizableImagePanel::OnSize(wxSizeEvent& event) {
    Refresh();
    event.Skip();
}

void wxResizableImagePanel::Render(wxDC& dc) {
    wxCoord width = 0;
    wxCoord height = 0;
    dc.GetSize(&width, &height);

    if (width != m_width || height != m_height) {
        // TODO: improve scaling performace
        // maybe resize using normal quality and then after some time
        // after the last resize, asynchronously rescale with high quality
        m_bitmap = wxBitmap(m_image.Scale(width, height, wxIMAGE_QUALITY_HIGH));
        m_width = width;
        m_height = height;
    }

    dc.DrawBitmap(m_bitmap, 0, 0, false);
}

void wxResizableImagePanel::SetImage(const wxImage& image) {
    m_image = wxImage(image);
}

void wxResizableImagePanel::SetImage(const wxString& filename, wxBitmapType format) {
    bool loaded_successfully = m_image.LoadFile(filename, format);
    if (!loaded_successfully) {
        throw std::runtime_error("Could not load image" + filename);
    }
}

BEGIN_EVENT_TABLE(wxResizableImagePanel, wxPanel)
    EVT_PAINT(wxResizableImagePanel::OnPaint)
    EVT_SIZE(wxResizableImagePanel::OnSize)
END_EVENT_TABLE()

