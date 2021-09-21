#include "wxResizableImagePanel.h"

wxResizableImagePanel::wxResizableImagePanel(wxFrame* parent, wxString filename, wxBitmapType format) : wxPanel(parent), m_image(), m_bitmap(), m_width(m_image.GetWidth()), m_height(m_image.GetHeight()) {
    bool loaded_successfully = m_image.LoadFile(filename, format);
    if (!loaded_successfully) {
        throw std::runtime_error("Could not load image" + filename);
    }
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
        m_bitmap = wxBitmap(m_image.Scale(width, height, wxIMAGE_QUALITY_HIGH));
        m_width = width;
        m_height = height;
    }

    dc.DrawBitmap(m_bitmap, 0, 0, false);
}

BEGIN_EVENT_TABLE(wxResizableImagePanel, wxPanel)
    EVT_PAINT(wxResizableImagePanel::OnPaint)
    EVT_SIZE(wxResizableImagePanel::OnSize)
END_EVENT_TABLE()

