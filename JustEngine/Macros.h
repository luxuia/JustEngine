#pragma once

const bool USE_WRAP_DRIVER = false;

const int SWAP_CHAIN_BUFFER_COUNT = 3;

#ifdef _WIN32 

#ifdef API_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#else 
#define DLL_EXPORT __declspec(dllimport)
#endif  // end api_export

#else

#define DLL_EXPORT

#endif // end _win32