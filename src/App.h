#pragma once

#include <memory>

#include <wx/wx.h>

#include "MainFrame.h"

class App : public wxApp {
public:
    App();
    virtual ~App() = default;
    virtual bool OnInit() override;

private:
    MainFrame* m_main_frame;
};

