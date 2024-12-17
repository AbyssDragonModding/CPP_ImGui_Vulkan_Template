#include "../include/MainWindow.h"

void MainWindow::RenderWindow()
{
    // Menu
    ImGui::Begin("Main Window - Vulkan");
    ImGui::Checkbox("Test Checkbox", &m_TestBool);
    ImGui::DragFloat("Drag Float", &m_TestFloat, 0.5f, 0.0f, 10.0f);
    ImGui::End();
}
