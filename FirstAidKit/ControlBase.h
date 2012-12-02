#pragma once

#include "ControlAppearanceBase.h"

class ATL_NO_VTABLE ControlBase
	: public ControlAppearanceBase
	, public GrymCore::ICommandAction
	, public GrymCore::ICommandAccelerator
{
protected:
	ControlBase();
	~ControlBase();

	BEGIN_COM_MAP(ControlBase)
		COM_INTERFACE_ENTRY(GrymCore::ICommandAction)
		COM_INTERFACE_ENTRY_FUNC(__uuidof(GrymCore::ICommandAccelerator), 0, ICommandAcceleratorQIFunc)
		COM_INTERFACE_ENTRY_CHAIN(ControlAppearanceBase)
	END_COM_MAP()

	void SetAccelerator(DWORD accelerator);

public: //ICommandAction
	// нужно определить в классе потомке
	STDMETHOD(raw_OnCommand)(void) PURE;

public: //ICommandAccelerator
	STDMETHOD(get_Accelerator)(LONG * pVal);

protected:
	DWORD accelerator_;

private:
	static HRESULT WINAPI ICommandAcceleratorQIFunc(void *pv, REFIID riid, LPVOID *ppv, DWORD dw);
};