#pragma once
#include "stdafx.h"
/// <summary>
/// Class TextErrorMessageSender has a function which sends a message with type 0x9B1552DB, which seems to do something with null text strings. Said function is then detoured in this mod.
/// </summary>
class TextErrorMessageSender {
public:
	char padding[0x80];
	void* func80h();
	void* func84h();

};

/// <summary>
/// This class inherits from ITextEdit so we can use its functions in detours.
/// </summary>
class TextApplier : public ITextEdit {
	
};