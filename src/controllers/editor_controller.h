#pragma once

#include <memory>
#include <filesystem>

#include "document.h"
#include "renderer.h"
#include "MainFrame.h"

class editor_controller {
public:
    editor_controller();
    editor_controller(const std::filesystem::path& pdf_path);
    editor_controller(const std::filesystem::path& pdf_path, std::filesystem::path& notes_path);
    ~editor_controller() = default;

    void start();
    void show_document_chooser();
    void on_about(wxCommandEvent& event);
    void on_exit(wxCommandEvent& event);
    void on_open(wxCommandEvent& event);

private:
    std::pair<int, int> get_screen_size() const;

    document m_document;
    renderer m_renderer;
    MainFrame* m_main_frame;
};

