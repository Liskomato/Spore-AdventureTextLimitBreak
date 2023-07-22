// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "TextLimitBreaker.h"
#include "TextErrorMessageSender.h"

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
	
	member_detour(UILayoutLoad_detour, UILayout, bool(const ResourceKey&, bool, uint32_t))
	{
		bool detoured(const ResourceKey & resourceKey, bool boolean, uint32_t parameter)
		{
			bool func = original_function(this, resourceKey, boolean, parameter);

			if (this->mResourceKey.instanceID == 0x23c919ea || this->mResourceKey.instanceID == 0x2cb74334) {
				this->FindWindowByID(0xCEFA1100)->AddWinProc(new TextLimitBreaker());
			}
			/*
			if (this->mResourceKey.instanceID == 0x93ab9d4b || this->mResourceKey.instanceID == 0xec4cfaba) {
				this->FindWindowByID(0xCEFF0000)->AddWinProc(new TextLimitBreaker());
			}*/

			if (this->mResourceKey.instanceID == 0x7250e3a1) {
				this->FindWindowByID(0x0710A140)->AddWinProc(new TextLimitBreaker());
			}

			return func;

		}
	};
	
	member_detour(TextError_dtr, TextErrorMessageSender, void* (void*)) {
		void* detoured(void* p1) {
			App::ConsolePrintF("Function 0x989170 called.");
			return original_function(this,p1);
		}

	};

	/*
	static_detour(ITextEditCon_detour, ITextEdit* ()) 
	{
		ITextEdit* detoured() {
			ITextEdit* fun = original_function();
			if (fun->ToWindow()->GetControlID() == 0xCEFA1100)
				fun->SetMaxTextLength(-1);
			return fun;
		}
	};
	*/
}
void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	UTFWin::UILayoutLoad_detour::attach(GetAddress(UTFWin::UILayout, Load));
//	UTFWin::ITextEditCon_detour::attach(GetAddress(UTFWin::ITextEdit,Create));
	
	UTFWin::TextError_dtr::attach(Address(0x989170));

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

