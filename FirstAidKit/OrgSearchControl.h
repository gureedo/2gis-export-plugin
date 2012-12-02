#pragma once
#include "ControlAppearanceBase.h"
#include "ControlAppearanceParams.h"

class ATL_NO_VTABLE COrgSearchControl
	: public ControlAppearanceBase
	, public GrymCore::IContainerControl
	, public GrymCore::ISearchGroupControl
{
public:
	static GrymCore::ISearchGroupControlPtr CreateInstance(
		const ControlAppearanceParams & appearance,
		const GrymCore::IGrymObjectFactory2Ptr & factory);

	~COrgSearchControl(void);

protected:
	COrgSearchControl(void);

	BEGIN_COM_MAP(COrgSearchControl)
		COM_INTERFACE_ENTRY(GrymCore::IContainerControl)
		COM_INTERFACE_ENTRY(GrymCore::ISearchGroupControl)
		COM_INTERFACE_ENTRY_CHAIN(ControlAppearanceBase)
	END_COM_MAP()

public:	//IContainerControl
	STDMETHOD(get_InternalControl)(IUnknown ** pVal);

public:	//ISearchGroupControl
	STDMETHOD(get_SearchEnabled)(VARIANT_BOOL * pVal);
	STDMETHOD(get_ClearEnabled)(VARIANT_BOOL * pVal);
	STDMETHOD(raw_FillCriteriaSet)(GrymCore::ICriteriaSet * pCritSet, VARIANT_BOOL * pVal);
	STDMETHOD(get_SearchDescription)(BSTR * pVal);
	STDMETHOD(get_SearchCaption)(BSTR * pVal);
	STDMETHOD(raw_Clear)();

private:
	void AdjustEditControl(const GrymCore::IGrymObjectFactory2Ptr & factory);

private:
	// Встроенный элемент управления "поле ввода"
	GrymCore::IGrymControlEditTextHolderPtr grymEditControl_;
};
