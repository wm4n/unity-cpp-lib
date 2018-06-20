#pragma once

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport) 
#else
#define DLL_API __declspec(dllimport) 
#endif

#include <stddef.h> // size_t

extern "C" {

	namespace SampleCppDll {

		/**
		 * Callback definition for GetLength and Append function
		 */
		typedef void(*TEXT_CALLBACK)(bool hasTextChanged, int newLength);
		
		/**
		 * Library class declaration
		 */
		class CustomString;

		/**
		 * Exported functions
		 */
		DLL_API CustomString* GetCustomString(const char* str, size_t strLength);

		DLL_API void DestroyString(CustomString* targetObj);

		DLL_API void GetString(CustomString* targetObj, char* buf, size_t length);

		DLL_API size_t GetLength(CustomString* targetObj);

		DLL_API void Append(CustomString* targetObj, const char* str, size_t strLength);

		DLL_API void SetCallback(CustomString* targetObj, TEXT_CALLBACK callback);

	}

} // extern "C"#pragma once
