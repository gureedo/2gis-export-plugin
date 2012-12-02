#include "StdAfx.h"
#include "ControlAppearanceBase.h"

ControlAppearanceBase::ControlAppearanceBase() { }

ControlAppearanceBase::~ControlAppearanceBase(void) { }

void ControlAppearanceBase::SetAppearance(const _bstr_t &tag, const _bstr_t &caption, const _bstr_t &description, IUnknown *icon)
{
	tag_ = tag;
	caption_ = caption;
	description_ = description;
	icon_ = icon;
}

void ControlAppearanceBase::SetPlacement(const _bstr_t &placement_code)
{
	placement_code_ = placement_code;
}

STDMETHODIMP ControlAppearanceBase::get_PlacementCode(BSTR *pVal)
{
	if (!pVal)
		return E_POINTER;
	*pVal = placement_code_.copy();
	return S_OK;
}

STDMETHODIMP ControlAppearanceBase::get_Tag(BSTR *pVal)
{
	if(!pVal)
		return E_POINTER;
	*pVal = tag_.copy();
	return S_OK;
}

STDMETHODIMP ControlAppearanceBase::get_Caption(BSTR *pVal)
{
	if(!pVal)
		return E_POINTER;
	*pVal = caption_.copy();
	return S_OK;
}

STDMETHODIMP ControlAppearanceBase::get_Description(BSTR *pVal)
{
	if(!pVal)
		return E_POINTER;
	*pVal = description_.copy();
	return S_OK;
}

STDMETHODIMP ControlAppearanceBase::get_Icon(IUnknown ** pVal)
{
	if(!pVal)
		return E_POINTER;
	*pVal = IUnknownPtr(icon_).Detach();
	return S_OK;
}