#include "stdafx.h"
#include "TextLimitBreaker.h"

TextLimitBreaker::TextLimitBreaker()
{
	if (Simulator::IsScenarioMode()) {
		resource = ScenarioMode.GetResource();
		data = ScenarioMode.GetData();
	}
	else {
		resource = nullptr;
		data = nullptr;
	}
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
	return kEventFlagBasicInput | kEventFlagAdvanced | kEventFlagLayout;
}

// The method that receives the message. The first thing you should do is probably
// checking what kind of message was sent...
bool TextLimitBreaker::HandleUIMessage(IWindow* window, const Message& message)
{
	if (window->GetControlID() == 0xCEFA1100 || window->GetControlID() == 0x0710A140) {
		ITextEditPtr textWindow = object_cast<ITextEdit>(window);
		if (window->GetNextWinProc(this) != nullptr) {
			auto* nextProc = window->GetNextWinProc(this);
			App::ConsolePrintF("Second WinProc flags: %#x", nextProc->GetEventFlags());
			if (window->GetNextWinProc(nextProc) != nullptr) {
				auto* secondProc = window->GetNextWinProc(nextProc);
				App::ConsolePrintF("Third WinProc flags: %#x", secondProc->GetEventFlags());
			}
		
		}
		if (window->GetControlID() == 0xCEFA1100) App::ConsolePrintF("0xCEFA1100 message: 0x%X", message.eventType);
		if (window->GetControlID() == 0x0710A140) App::ConsolePrintF("0x0710A140 message: 0x%X", message.eventType);

		App::ConsolePrintF("Text limit: %d", textWindow->GetMaxTextLength());

		if (message.IsType(kMsgButtonSelect)) {

			textWindow->SetMaxTextLength(-1);
			App::ConsolePrintF("New text limit: %d", textWindow->GetMaxTextLength());
			return true;
		}
		if (message.IsType(0x9B1552DB) || message.IsType(kMsgTextChanged)) {
			textWindow->SetMaxTextLength(-1);
			if (Simulator::IsScenarioMode()) {
				auto* resource = ScenarioMode.GetResource();
				string16 winText = textWindow->GetText();
				if (window->GetControlID() == 0xCEFA1100) {
					for (auto& act : resource->mActs) {
						for (auto& goal : act.mGoals) {
							for (auto& dialog : goal.mDialogs) {
								App::ConsolePrintF("Dialog match?\ndialog.mText.mNonLocalizedString: %ls\ntextWindow->GetText(): %ls", dialog.mText.mNonLocalizedString, winText);
								if (dialog.mText.mNonLocalizedString == winText) {

									textWindow->SetText(dialog.mText.mNonLocalizedString.c_str(), -1);
									return true;
								}
							}
						}
					}
					for (auto& mClass : resource->mClasses) {
						for (auto& act : mClass.second.mActs) {
							for (auto& dialog : act.mDialogsChatter) {
								if (dialog.mText.mNonLocalizedString == winText) {
									App::ConsolePrintF("Dialog match?\ndialog.mText.mNonLocalizedString: %ls\ntextWindow->GetText(): %ls", dialog.mText.mString.GetText(), winText);
									textWindow->SetText(dialog.mText.mNonLocalizedString.c_str(), -1);
									return true;
								}
							}
							for (auto& dialog : act.mDialogsInspect) {
								if (dialog.mText.mNonLocalizedString == winText) {
									App::ConsolePrintF("Dialog match?\ndialog.mText.mNonLocalizedString: %ls\ntextWindow->GetText(): %ls", dialog.mText.mString.GetText(), winText);
									textWindow->SetText(dialog.mText.mNonLocalizedString.c_str(), -1);
									return true;
								}
							}
						}
					}
				}
			}
		}
			
		if	(message.IsType(kMsgLayout)) {
			textWindow->SetMaxTextLength(-1);
			App::ConsolePrintF("New text limit: %d", textWindow->GetMaxTextLength());
			return false;
		}
	}
	
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
