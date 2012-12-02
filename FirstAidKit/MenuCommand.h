#pragma once

#include "ControlBase.h"
#include "ControlAppearanceParams.h"

class ATL_NO_VTABLE MenuCommand
	: public ControlBase
{
public:
	static GrymCore::ICommandActionPtr CreateInstance(const ControlAppearanceParams &appearance, DWORD accelerator = 0);

protected:
	MenuCommand() {}
	~MenuCommand() {}

public:	//ICommandAction
	STDMETHOD(raw_OnCommand)() { return S_OK; }
};