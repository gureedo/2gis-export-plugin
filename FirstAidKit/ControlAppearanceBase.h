#pragma once

class ATL_NO_VTABLE ControlAppearanceBase
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IControlPlacement
	, public GrymCore::IControlAppearance
{
protected:
	ControlAppearanceBase();
	~ControlAppearanceBase(void);

	void SetAppearance(const _bstr_t &tag, const _bstr_t &caption, const _bstr_t &description = "", IUnknown *icon = 0);
	void SetPlacement(const _bstr_t &placement_code);

	BEGIN_COM_MAP(ControlAppearanceBase)
		COM_INTERFACE_ENTRY(GrymCore::IControlPlacement)
		COM_INTERFACE_ENTRY(GrymCore::IControlAppearance)
	END_COM_MAP()

public: // GrymCore::IControlPlacement 
	STDMETHOD(get_PlacementCode)(BSTR *pVal);

public: // GrymCore::IControlAppearance
	STDMETHOD(get_Tag)(BSTR *pVal);
	STDMETHOD(get_Caption)(BSTR *pVal);
	STDMETHOD(get_Description)(BSTR *pVal);
	STDMETHOD(get_Icon)(IUnknown ** pVal);

protected:
	_bstr_t placement_code_;
	_bstr_t tag_;
	_bstr_t caption_;
	_bstr_t description_;
	IUnknownPtr icon_;
};