#include "renderer.h"
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

Renderer::Renderer(HWND windowHandle, uint32_t width, uint32_t height)
    : m_windowHandle(windowHandle), m_width(width), m_height(height) {}

Renderer::~Renderer() {}

void Renderer::OnInit()
{
    LoadPipeline();
    LoadAssets();
}

void Renderer::OnDestroy()
{
}

void Renderer::OnRender()
{
}

void Renderer::OnUpdate()
{
}

void Renderer::LoadPipeline()
{
}

void Renderer::LoadAssets()
{
}

void Renderer::PopulateCommandList()
{
}

void Renderer::WaitForPreviousFrame()
{
}
