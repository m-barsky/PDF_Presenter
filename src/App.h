#pragma once

#include <memory>

#include <wx/wx.h>

#include "EditorController.h"

class App : public wxApp {
public:
    App();
    virtual ~App() = default;
    virtual bool OnInit() override;

private:
    std::unique_ptr<EditorController> m_editor_controller;
};

