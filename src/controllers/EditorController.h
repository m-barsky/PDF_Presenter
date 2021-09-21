#pragma once

#include <memory>
#include <filesystem>

#include "Document.h"
#include "MainFrame.h"

class EditorController {
public:
    EditorController();
    EditorController(const std::filesystem::path& pdf_path);
    EditorController(const std::filesystem::path& pdf_path, std::filesystem::path& notes_path);
    ~EditorController() = default;

    void start();

    void show_document_chooser();

private:
    Document m_document;
    MainFrame* m_main_frame;
};

