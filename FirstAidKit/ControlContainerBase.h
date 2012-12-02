#pragma once

class ATL_NO_VTABLE ControlContainerBase
	: public ControlAppearanceBase
	, public GrymCore::IContainerControl
{
protected:
	ControlContainerBase() { }
	~ControlContainerBase() { }

	BEGIN_COM_MAP(ControlContainerBase)
		COM_INTERFACE_ENTRY(GrymCore::IContainerControl)
		COM_INTERFACE_ENTRY_CHAIN(ControlAppearanceBase)
	END_COM_MAP()

public:	//GrymCore::IContainerControl
	STDMETHOD(get_InternalControl)(IUnknown** pVal) PURE;
};