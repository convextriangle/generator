#ifndef UTILS_H
#define UTILS_H

#include <WTypesbase.h>

#include <d3d12.h>
#include <source_location>
#include <string>
#include <wrl.h>

inline std::string HrToString(HRESULT hr);

inline void ThrowIfFailed(HRESULT hr, const std::source_location location = std::source_location::current());

Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(const std::string &contents, const std::string &entrypoint,
                                               const std::string &targetProfile);

std::string ReadFileContents(const std::string &path);

struct RGBA8Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

#endif
