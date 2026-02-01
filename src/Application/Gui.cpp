#include "Gui.h"

#include "../Performance/Trace.h"
#include "Window.h"

Gui *Gui::instancePtr = nullptr;
Gui::Gui() 
{
    TRACE_FUNCTION();
    assert(instancePtr == nullptr && "The GUI is already instantiated");
    instancePtr = nullptr;

    const auto context = Window::instance.getContext();
    if (context == nullptr) 
    {
        return;
    }

    IMGUI_CKECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(context, true);
    ImGui_ImplOpenGL3_Init("#version 450 core");
}