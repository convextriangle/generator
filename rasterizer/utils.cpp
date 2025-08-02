#include "utils.h"
#include <d3d12.h>
#include <d3dcompiler.h>
#include <fstream>
#include <sstream>
#include <wrl.h>

using namespace Microsoft::WRL;

inline std::string HrToString(HRESULT hr)
{
    char *errorMsg = nullptr;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
                   hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&errorMsg), 0, nullptr);

    std::string message = errorMsg ? errorMsg : "Unknown error";
    if (errorMsg)
        LocalFree(errorMsg);
    return message;
}

inline void ThrowIfFailed(HRESULT hr, const std::source_location location)
{
    if (SUCCEEDED(hr))
    {
        return;
    }

    std::string error = HrToString(hr);
    throw std::exception(error.c_str());
}

std::string ReadFileContents(const std::string &path)
{
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file)
    {
        throw std::exception(("shader file not found: " + path).c_str());
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

ComPtr<ID3DBlob> CompileShader(const std::string &contents, const std::string &entrypoint,
                               const std::string &targetProfile)
{
    ComPtr<ID3DBlob> errorBlob;
    ComPtr<ID3DBlob> shaderBlob;

#if defined(_DEBUG)
    // Enable better shader debugging with the graphics debugging tools.
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    UINT compileFlags = 0;
#endif

    auto hr = D3DCompile(contents.c_str(), contents.size(), "", nullptr, nullptr, entrypoint.c_str(),
                         targetProfile.c_str(), compileFlags, 0, &shaderBlob, &errorBlob);
    std::string error = (const char*)errorBlob->GetBufferPointer();
    ThrowIfFailed(hr);

    return shaderBlob;
}
