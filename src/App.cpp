#include "App.h"

#include "MainFrame.h"

wxIMPLEMENT_APP(App);

App::App() : m_editor_controller() {

}

bool App::OnInit() {
    if(!wxApp::OnInit()) {
        return false;
    }

    m_editor_controller = std::make_unique<EditorController>();

    m_editor_controller->start();

    return true;
}

