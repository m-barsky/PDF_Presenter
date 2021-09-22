#pragma once

#include <filesystem>
#include <fstream>
#include <cassert>

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

private:
    std::filesystem::path m_pdf_path;
    std::ifstream m_pdf_file;

    std::filesystem::path m_notes_path;
    std::ifstream m_notes_file;
};

