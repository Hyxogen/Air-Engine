#pragma once
#include <cstdint>

#ifndef AIR_HASH_CUSTOM
#define AIR_HASH_FNV1A
#define AIR_HASH_32BIT
#endif

#ifdef AIR_HASH_FNV1A
#ifdef AIR_HASH_32BIT
constexpr unsigned int Hash(const char* str, unsigned int n, unsigned int basis = UINT32_C(2166136261)) {
    return n == 0 ? basis : Hash(str + 1, n - 1, (basis ^ str[0]) * UINT32_C(16777619));
}
#else
#error Air engine does not support this hashing function
#endif
#else
#error No valid hash function defined
#endif