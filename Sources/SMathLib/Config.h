
#ifndef _SMATHLIB_CONFIG_H_
#define _SMATHLIB_CONFIG_H_

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Find the operation system.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define SMATHLIB_OS_WIN32
#elif defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
	#define SMATHLIB_OS_WIN64
#elif defined(__APPLE__)
	#define SMATHLIB_OS_MAC
#elif defined(__linux__) || defined(__linux)
	#define SMATHLIB_OS_LINUX
#endif
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
// Define a common flag for 32 and 64 bit windows.
#if defined(SMATHLIB_OS_WIN32) || defined(SMATHLIB_OS_WIN64)
	#define SMATHLIB_OS_WINDOWS
#endif
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//! Used for creating or consuming DLL's.
#if defined(SMATHLIB_OS_WINDOWS)
	#if defined(SMATHLIB_EXPORTS)
		#define SMATHLIB_DLL_API __declspec(dllexport)   // Export DLL information.
	#else
		#define SMATHLIB_DLL_API __declspec(dllimport)   // Import DLL information.
	#endif
#else
	#define SMATHLIB_DLL_API
#endif
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

#endif // _SMATHLIB_CONFIG_H_
