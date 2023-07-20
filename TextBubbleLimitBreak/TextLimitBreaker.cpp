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
	if (window->GetControlID() == 0xCEFF0000 && message.IsType(kMsgButtonSelect) && WindowManager.GetMainWindow()->FindWindowByID(0x07DE6958)->IsAncestorOf(window)) {
		eastl::vector<ITextEditPtr> textBoxes;
		eastl::vector<IWindowPtr> goalButtons;
		
		int goalIndex = 0;
		int actIndex = 0;

		for (IWindowPtr child : window->children()) {
			if (child->FindWindowByID(0xCEFA1100) != nullptr) {
				textBoxes.emplace_back(object_cast<ITextEdit*>(child->FindWindowByID(0xCEFA1100)));
			}
		}
		IWindowPtr EditGoalsUI = WindowManager.GetMainWindow()->FindWindowByID(0x0757ACB8);
		for (IWindowPtr child : EditGoalsUI->children()) {
			if (child->FindWindowByID(0x074656A0) != nullptr) {
				goalButtons.emplace_back(child->FindWindowByID(0x074656A0));
			}
		}
		for (int i = 0;i < goalButtons.size();i++) {
			if (message.IsSource(goalButtons[i].get())) {
				goalIndex = i;
				break;
			}
		}

		if (data != nullptr)
		int actIndex = data->GetEditModeActIndex();
		if (resource != nullptr) {
			auto& indexedTarget = resource->mActs[actIndex].mGoals[goalIndex].mDialogs;
			for (int i = 0; i < indexedTarget.size(); i++) {
				textBoxes[i]->SetMaxTextLength(-1);
				if (indexedTarget[i].mText.mLocalizedStringInstanceID != 0 && indexedTarget[i].mText.mLocalizedStringTableID != 0) {
					textBoxes[i]->SetText(indexedTarget[i].mText.mString.GetText(), -1);
					App::ConsolePrintF("Set localized act %d goal %d dialog %d text into the corresponding text box.",actIndex+1,goalIndex+1,i+1);
				}
				else if ((indexedTarget[i].mText.mNonLocalizedString != u"") || (indexedTarget[i].mText.mNonLocalizedString != u"***")) {
					textBoxes[i]->SetText(indexedTarget[i].mText.mNonLocalizedString.c_str(), -1);
					App::ConsolePrintF("Set unlocalized act %d goal %d dialog %d text into the corresponding text box.", actIndex+1, goalIndex+1,i+1);
				}
			}
			return true;
		}
		return false;
	}
	if (window->GetControlID() == 0xCEFA1100 || window->GetControlID() == 0x0710A140) {
		ITextEditPtr textWindow = object_cast<ITextEdit>(window);
		
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
		if (window->GetControlID() == 0xCEFA1100) App::ConsolePrintF("0xCEFA1100 message: 0x%X", message.eventType);
		if (window->GetControlID() == 0x0710A140) App::ConsolePrintF("0x0710A140 message: 0x%X", message.eventType);

		App::ConsolePrintF("Text limit: %d", textWindow->GetMaxTextLength());

		if (message.IsType(kMsgButtonSelect) || message.IsType(0x9B1552DB) || message.IsType(kMsgTextChanged)) {

			textWindow->SetMaxTextLength(-1);
			App::ConsolePrintF("New text limit: %d", textWindow->GetMaxTextLength());
			return true;
		}
		/*
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
		*/
	}
	
	// Return true if the message was handled, and therefore no other window procedure should receive it.
	return false;
}
