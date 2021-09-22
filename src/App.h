#pragma once

#include <memory>

#include <wx/wx.h>

#include "editor_controller.h"

class App : public wxApp {
public:
    App();
    virtual ~App() = default;
    virtual bool OnInit() override;

private:
    std::unique_ptr<editor_controller> m_editor_controller;
};

