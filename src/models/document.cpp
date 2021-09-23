#include "document.h"

#include <cassert>

#include "poppler/cpp/poppler-document.h"

document::document()
    : m_pdf_path(),
    m_pdf_file(),
    m_pdf_document(),
    m_notes_path(), 
    m_notes_file(),
    m_dirty(false) {

}

document::document(const std::filesystem::path& pdf_path)
    : m_pdf_path(pdf_path),
    m_pdf_file(m_pdf_path, std::ios::in | std::ios::binary),
    m_pdf_document(),
    m_notes_path(std::filesystem::path(m_pdf_path).replace_extension("txt")),
    m_notes_file(m_notes_path),
    m_dirty(false) {

    if (!m_pdf_file.is_open()) {
        throw std::runtime_error("couldn't open file: " + m_pdf_path.string());
    }

    if (!m_notes_file.is_open()) {
        throw std::runtime_error("couldn't open file: " + m_notes_path.string());
    }
}

document::document(const std::filesystem::path& pdf_path, const std::filesystem::path& notes_path)
    : m_pdf_path(pdf_path),
    m_pdf_file(m_pdf_path, std::ios::in | std::ios::binary),
    m_pdf_document(),
    m_notes_path(notes_path),
    m_notes_file(m_notes_path),
    m_dirty(false) {
    
}

std::filesystem::path document::name() const {
    return m_pdf_path.filename();
}

std::filesystem::path document::path() const {
    return m_pdf_path;
}

bool document::is_open() const {
    assert(m_pdf_file.is_open() == m_notes_file.is_open());
    return m_pdf_file.is_open() && m_notes_file.is_open();
}

document::operator bool() const {
    return is_open();
}

bool document::dirty() const {
    return m_dirty;
}

void document::flush() {

}

int document::page_count() const {
    return m_pdf_document->pages();
}

