#pragma once

#include <filesystem>
#include <fstream>

#include "poppler/cpp/poppler-document.h"

#include "undeleted_ptr.h"

class document {
public:
    document();
    document(const std::filesystem::path& pdf_path);
    document(const std::filesystem::path& pdf_path, const std::filesystem::path& notes_path);

    document(const document&) = delete;
    document(document&&) = default;

    document& operator=(const document&) = delete;
    document& operator=(document&&) = default;

    ~document() = default;

    std::filesystem::path name() const;
    std::filesystem::path path() const;

    bool is_open() const; 
    explicit operator bool() const;

    bool dirty() const;
    void flush();

    int page_count() const;

private:
    std::filesystem::path m_pdf_path;
    std::ifstream m_pdf_file;
    undeleted_ptr<poppler::document> m_pdf_document;

    std::filesystem::path m_notes_path;
    std::ifstream m_notes_file;

    bool m_dirty;
};

