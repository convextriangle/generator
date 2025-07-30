#ifndef UTILS_H
#define UTILS_H

#include <WTypesbase.h>

#include <source_location>
#include <string>

inline static std::string HrToString(HRESULT hr);

inline static void ThrowIfFailed(
    HRESULT hr,
    const std::source_location location = std::source_location::current());

#endif
