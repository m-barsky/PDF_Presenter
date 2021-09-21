#pragma once

#include <filesystem>
#include <fstream>

class Document {
public:
    Document();
    Document(const std::filesystem::path& pdf_path);
    Document(const std::filesystem::path& pdf_path, const std::filesystem::path& notes_path);

    Document(const Document&) = delete;
    Document(Document&&) = default;

    Document& operator=(const Document&) = delete;
    Document& operator=(Document&&) = default;

    ~Document() = default;

    std::filesystem::path name() const;
    std::filesystem::path path() const;

private:
    std::filesystem::path m_pdf_path;
    std::ifstream m_pdf_file;

    std::filesystem::path m_notes_path;
    std::ifstream m_notes_file;
};

