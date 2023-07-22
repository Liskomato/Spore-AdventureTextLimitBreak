#pragma once

#include <Spore\BasicIncludes.h>

#define TextLimitBreakerPtr intrusive_ptr<TextLimitBreaker>

// To avoid repeating UTFWin:: all the time.
using namespace UTFWin;

class TextLimitBreaker 
	: public IWinProc
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("TextLimitBreaker");
	
	///
	/// Pointers to main scenario classes in case we need to fetch information from them. We assign the data in the constructor, and deassign it in the destructor.
	/// 
//	cScenarioResourcePtr resource;
//	cScenarioDataPtr data;

	TextLimitBreaker();
	~TextLimitBreaker();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
	
	int GetEventFlags() const override;
	// This is the function you have to implement, called when a window you added this winproc to received an event
	bool HandleUIMessage(IWindow* pWindow, const Message& message) override;
	
};
