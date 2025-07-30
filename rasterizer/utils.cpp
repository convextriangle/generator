#include "utils.h"

inline std::string HrToString(HRESULT hr) {
  char* errorMsg = nullptr;
  FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                     FORMAT_MESSAGE_IGNORE_INSERTS,
                 nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                 reinterpret_cast<LPSTR>(&errorMsg), 0, nullptr);

  std::string message = errorMsg ? errorMsg : "Unknown error";
  if (errorMsg) LocalFree(errorMsg);
  return message;
}

inline void ThrowIfFailed(HRESULT hr, const std::source_location location) {
  if (SUCCEEDED(hr)) {
    return;
  }

  std::string error = HrToString(hr);
  throw std::exception(error.c_str());
}
