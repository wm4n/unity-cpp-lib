#include "SampleCppDll.h"

namespace SampleCppDll {

	/**
	 * pimpl implementation to hide logic from the header files
	 */
	class CustomString::impl {
	private:
	public:
		std::string mText;
		TEXT_CALLBACK mCallback;

		void init(std::string inputText) {
			mText = std::string(inputText);
		}
	};

	/**
	 * default constructor
	 */
	CustomString::CustomString()
		: CustomString(std::string("")) {
	}

	/**
	 * constructor takes a given string parameter
	 */
	CustomString::CustomString(const std::string& inputText) {
		pimpl = std::make_unique<impl>();
		pimpl->init(inputText);
	}

	/**
	 * retreive the string and put in into a given buffer
	 */
	void CustomString::GetString(char* buf, size_t length) {
		strncpy_s(buf, length, pimpl->mText.c_str(), pimpl->mText.size());
	}

	/**
	 * retreive the length of the string
	 */
	size_t CustomString::GetLength() {
		if (nullptr != pimpl->mCallback) {
			pimpl->mCallback(false, pimpl->mText.size());
		}
		return pimpl->mText.size();
	}

	/**
	 * append to the string
	 */
	void CustomString::Append(const std::string& str) {
		pimpl->mText.append(str);
		if (nullptr != pimpl->mCallback) {
			pimpl->mCallback(str.size() > 0, pimpl->mText.size());
		}
	}

	/**
	 * set callback to listen for the GetLength and Append call. This
	 * is for demostrating how to use callback from unity
	 */
	void CustomString::SetCallback(TEXT_CALLBACK callback) {
		pimpl->mCallback = callback;
	}

	/**
	 * DLL exported function
	 * create a new instance of the class and return it
	 */
	CustomString* GetCustomString(const char* str, size_t strLength) {
		return new CustomString(std::string(str, strLength));
	}

	/**
	 * DLL exported function
	 * destroy the created instance and release memory
	 */
	void DestroyString(CustomString* targetObj) {
		delete targetObj;
	}

	/**
	 * DLL exported function
	 * retreive the string of an instance
	 */
	void GetString(CustomString* targetObj, char* buf, size_t length) {
		targetObj->GetString(buf, length);
	}

	/**
	* DLL exported function
	* retreive the length of the string for an instance
	*/
	size_t GetLength(CustomString* targetObj) {
		return targetObj->GetLength();
	}

	/**
	* DLL exported function
	* append string for an instance
	*/
	void Append(CustomString* targetObj, const char* text, size_t textLength) {
		return targetObj->Append(std::string(text, textLength));
	}

	/**
	* DLL exported function
	* set callback for listening GetLength and Append for an instance
	*/
	void SetCallback(CustomString* targetObj, TEXT_CALLBACK callback) {
		targetObj->SetCallback(callback);
	}

}