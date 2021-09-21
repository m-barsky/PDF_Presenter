#include "App.h"

#include "MainFrame.h"

wxIMPLEMENT_APP(App);

App::App() : m_main_frame() {

}

bool App::OnInit() {
    if(!wxApp::OnInit()) {
        return false;
    }

    m_main_frame = new MainFrame();
    m_main_frame->Show(true);

    m_main_frame->ChoosePdfFile();

    return true;
}

