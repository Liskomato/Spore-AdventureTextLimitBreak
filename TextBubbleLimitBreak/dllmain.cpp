// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "TextLimitBreaker.h"
#include "TextLimitBreakClasses.h"

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
}

namespace UTFWin {
	/// <summary>
	/// We detour UILayout::Load to apply our own WinProcs to some of the windows found here. 
	/// 
	/// Basically, these win procs then allow us to modify some of these windows without fear of repercussions, undefined behaviour or glitches.
	/// </summary>
	member_detour(UILayoutLoad_detour, UILayout, bool(const ResourceKey&, bool, uint32_t))
	{
		bool detoured(const ResourceKey & resourceKey, bool boolean, uint32_t parameter)
		{
			bool func = original_function(this, resourceKey, boolean, parameter);

			if (this->mResourceKey.instanceID == 0x23c919ea || this->mResourceKey.instanceID == 0x2cb74334) {
				this->FindWindowByID(0xCEFA1100)->AddWinProc(new TextLimitBreaker());
			}

			if (this->mResourceKey.instanceID == 0x7250e3a1) {
				this->FindWindowByID(0x0710A140)->AddWinProc(new TextLimitBreaker());
			}

			return func;

		}
	};
	

	member_detour(TextApplier_dtr, TextApplier, bool(uint32_t*, uint32_t, void*, int, float)) {
	
		bool detoured(uint32_t * p1, uint32_t p2, void* p3, int p4, float p5) {
			/// Turning this text editor into a Window class intrusive pointer
			IWindowPtr thisWindow = this->ToWindow();
			/// Checking what type of window we're working with. These are all text edit windows found in the Adventure Editor.
			if (thisWindow->GetControlID() == 0xCEFA1100 || 
				thisWindow->GetControlID() == 0x0710A140 || 
				thisWindow->GetControlID() == 0x07172970 || 
				thisWindow->GetControlID() == 0x07172950 ||
				thisWindow->GetControlID() == 0x07172960 ||
				thisWindow->GetControlID() == 0x0743B978 )
			{
				this->SetMaxTextLength(-1);		// If match is found, set the max text length to -1 (basically unlimited)
			}
			bool func = original_function(this, p1, p2, p3, p4, p5);    // Afterwards, we resume the original function and end the detour here.
			return func;
		}
	};

	member_detour(TextError_dtr, TextErrorMessageSender, void* (void*)) {
		void* detoured(void* p1) {
	//		MessageBoxW(NULL,L"Function address 0x989170 (in March 2017 version) was called. This means the error message 0x9B1552DB was sent, so applying the extended text has failed.\n\nIf you get this error message, please contact Liskomato on GitHub or Discord so they can look on this matter.\nTIP: You can read this error message again in the cheat console in case you close this window.", L"Adventure Text Limit Break: TextErrorMessageSender", MB_OK | MB_ICONWARNING);
	//		App::ConsolePrintF("Text Limit Break: Function address 0x989170 (in March 2017 version) was called. This means the error message 0x9B1552DB was sent, so applying the extended text has failed.\n\nIf you get this error message, please contact Liskomato on GitHub or Discord so they can look on this matter.");
			return original_function(this,p1);
		}

	};

}
void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Detours of functions that exist in the SDK
	UTFWin::UILayoutLoad_detour::attach(GetAddress(UTFWin::UILayout, Load));
	
	// Detours of non-SDK functions.
	UTFWin::TextError_dtr::attach(Address(ModAPI::ChooseAddress(0x989520,0x989170)));
	UTFWin::TextApplier_dtr::attach(Address(ModAPI::ChooseAddress(0x98c7f0,0x98c4d0)));

	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

