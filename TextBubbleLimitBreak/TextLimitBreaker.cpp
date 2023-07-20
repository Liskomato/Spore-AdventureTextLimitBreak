#include "stdafx.h"
#include "TextLimitBreaker.h"

TextLimitBreaker::TextLimitBreaker()
{
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
	if (window->GetControlID() == 0xCEFA1100) App::ConsolePrintF("0xCEFA1100 message: 0x%X", message.eventType);
	if (window->GetControlID() == 0x0710A140) App::ConsolePrintF("0x0710A140 message: 0x%X", message.eventType);

	ITextEditPtr textWindow = object_cast<ITextEdit>(window);
	App::ConsolePrintF("Text limit: %d", textWindow->GetMaxTextLength());

	if ((message.IsType(kMsgButtonSelect) || message.IsType(0x9B1552DB)) && (window->GetControlID() == 0xCEFA1100 || window->GetControlID() == 0x0710A140)) {
		
		textWindow->SetMaxTextLength(-1);
		App::ConsolePrintF("New text limit: %d", textWindow->GetMaxTextLength());
		return true;
	}
	
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
