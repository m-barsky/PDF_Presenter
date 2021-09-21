#include "Document.h"

Document::Document()
    : m_pdf_path(),
    m_pdf_file(), 
    m_notes_path(), 
    m_notes_file() {

}

Document::Document(const std::filesystem::path& pdf_path)
    : m_pdf_path(pdf_path),
    m_pdf_file(m_pdf_path, std::ios::in | std::ios::binary),
    m_notes_path(std::filesystem::path(m_pdf_path).replace_extension("txt")),
    m_notes_file(m_notes_path) {

}

Document::Document(const std::filesystem::path& pdf_path, const std::filesystem::path& notes_path)
    : m_pdf_path(pdf_path),
    m_pdf_file(m_pdf_path, std::ios::in | std::ios::binary),
    m_notes_path(notes_path),
    m_notes_file(m_notes_path) {

}

std::filesystem::path Document::name() const {
    return m_pdf_path.filename();
}

std::filesystem::path Document::path() const {
    return m_pdf_path;
}

