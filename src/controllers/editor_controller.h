#pragma once

#include <memory>
#include <filesystem>

#include "document.h"
#include "MainFrame.h"

class editor_controller {
public:
    editor_controller();
    editor_controller(const std::filesystem::path& pdf_path);
    editor_controller(const std::filesystem::path& pdf_path, std::filesystem::path& notes_path);
    ~editor_controller() = default;

    void start();

    void show_document_chooser();

private:
    document m_document;
    MainFrame* m_main_frame;
};

