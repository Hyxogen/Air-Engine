#include "airpch.h"
#pragma once

#ifndef AIR_HASH_CUSTOM
#define AIR_HASH_FNV1A
#define AIR_HASH_32BIT
#endif

#ifdef AIR_HASH_FNV1A
#ifdef AIR_HASH_32BIT
/// <summary>
/// Non-cryptografic hash function that can be resolved at compile time
/// </summary>
/// <param name="str">String to hash</param>
/// <param name="n">Length of string in characters</param>
/// <param name="basis">Number for hashing see FNV1A algorithm for more</param>
/// <returns>Unique uint32 for str</returns>
constexpr uint32 Hash(const char* str, uint32 n, uint32 basis = UINT32_C(2166136261)) {
	return n == 0 ? basis : Hash(str + 1, n - 1, (basis ^ str[0]) * UINT32_C(16777619));
}
#else
#error Air engine does not support this hashing function
#endif
#else
#error No valid hash function defined
#endif