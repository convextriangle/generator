#ifndef RENDERER_H
#define RENDERER_H

#include "framework.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <dxgi1_6.h>
#include <d3dx12.h>

class Renderer
{
public:
	Renderer(HWND windowHandle, uint32_t width, uint32_t height);
	~Renderer();
	void OnInit();
	void OnDestroy();
	void OnRender();
	void OnUpdate(const std::vector<uint8_t> &bitmapData);
private:
	HWND m_windowHandle;
	const uint32_t m_width;
	const uint32_t m_height;
    static constexpr UINT FrameCount = 2;
    static constexpr UINT TexturePixelSize = 4;

    struct Vertex
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT2 uv;
    };

    // Pipeline objects.
    D3D12_VIEWPORT m_viewport;
    D3D12_RECT m_scissorRect;
    Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapChain;
    Microsoft::WRL::ComPtr<ID3D12Device> m_device;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
    Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_srvHeap;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_textureUploadHeap;
    UINT m_rtvDescriptorSize;

    // App resources.
    Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_texture;

    // Synchronization objects.
    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue;

    void LoadPipeline();
    void LoadAssets();
    void SetupTexture(const std::vector<uint8_t>& texture);
    void PopulateCommandList();
    void WaitForPreviousFrame();
    void UploadTexture(const std::vector<uint8_t>& data);
    D3D12_RESOURCE_DESC GetTextureDescription();
    std::vector<uint8_t> m_texturePixelData;
};

#endif