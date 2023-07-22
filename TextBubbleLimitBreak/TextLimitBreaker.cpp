#include "stdafx.h"
#include "TextLimitBreaker.h"

TextLimitBreaker::TextLimitBreaker()
{
	/*
	if (Simulator::IsScenarioMode()) {
		resource = ScenarioMode.GetResource();
		data = ScenarioMode.GetData();
	}
	else {
		resource = nullptr;
		data = nullptr;
	}
	*/
}


TextLimitBreaker::~TextLimitBreaker()
{
}

// For internal use, do not modify.
int TextLimitBreaker::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int TextLimitBreaker::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* TextLimitBreaker::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(IWinProc);
	CLASS_CAST(TextLimitBreaker);
	return nullptr;
}

// This method returns a combinations of values in UTFWin::EventFlags.
// The combination determines what types of events (messages) this window procedure receives.
// By default, it receives mouse/keyboard input and advanced messages.
int TextLimitBreaker::GetEventFlags() const
{
	return kEventFlagBasicInput | kEventFlagAdvanced;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool TextLimitBreaker::HandleUIMessage(IWindow* window, const Message& message)
{
	// ITextEditPtr textWindow = object_cast<ITextEdit>(window);
		
	/* Used to get information out of the WinProcs for debugging.
	if (window->GetNextWinProc(this) != nullptr) {
		auto* nextProc = window->GetNextWinProc(this);
		App::ConsolePrintF("Second WinProc flags: %#x", nextProc->GetEventFlags());
		if (window->GetNextWinProc(nextProc) != nullptr) {
			auto* secondProc = window->GetNextWinProc(nextProc);
				App::ConsolePrintF("Third WinProc flags: %#x", secondProc->GetEventFlags());
		}
	
	}
	*/

	//	App::ConsolePrintF("Text limit: %d", textWindow->GetMaxTextLength());

	if (message.IsType(kMsgTextChanged)) {
		ITextEditPtr textWindow = object_cast<ITextEdit>(window);
		textWindow->SetMaxTextLength(-1);
	//	App::ConsolePrintF("New text limit: %d", textWindow->GetMaxTextLength());
		return true;
	}
	
	
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
