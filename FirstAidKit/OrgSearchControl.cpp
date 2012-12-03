#include "StdAfx.h"
#include <sstream>
#include "OrgSearchControl.h"
#include "OrgDirectoryCustomController.h"

COrgSearchControl::COrgSearchControl(void)
{
}

COrgSearchControl::~COrgSearchControl(void)
{
}

GrymCore::ISearchGroupControlPtr COrgSearchControl::CreateInstance(
	const ControlAppearanceParams & appearance,
	const GrymCore::IGrymObjectFactory2Ptr & factory)
{
	ATL::CComObject<COrgSearchControl> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<COrgSearchControl>::CreateInstance(&obj));
	GrymCore::ISearchGroupControlPtr rv = obj;
	ATLASSERT(NULL != rv);

	obj->SetPlacement(appearance.placement_code);
	obj->SetAppearance(appearance.tag, appearance.caption, appearance.description, appearance.icon);

	obj->AdjustEditControl(factory);

	return rv;
}

void COrgSearchControl::AdjustEditControl(const GrymCore::IGrymObjectFactory2Ptr & factory)
{
	grymEditControl_ = factory->CreateGrymControl(GrymCore::GrymControlTypeEdit);
	GrymCore::IGrymControlPtr grymControl = grymEditControl_;
	grymControl->Style = GrymCore::GrymControlStyleCaption;
	grymControl->Width = 170;
	grymControl->Height = 25;
}

STDMETHODIMP COrgSearchControl::get_InternalControl(IUnknown ** pVal)
{
	try
	{
		if (!pVal)
			return E_POINTER;

		*pVal = IUnknownPtr(grymEditControl_).Detach();

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::get_SearchEnabled(VARIANT_BOOL * pVal)
{
	try
	{
		if (!pVal)
			return E_POINTER;

		*pVal = (grymEditControl_->EditText.length() != 0) ? VARIANT_TRUE : VARIANT_FALSE;

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::get_ClearEnabled(VARIANT_BOOL * pVal)
{
	return get_SearchEnabled(pVal);
}

STDMETHODIMP COrgSearchControl::raw_FillCriteriaSet(GrymCore::ICriteriaSet * pCritSet, VARIANT_BOOL * pVal)
{
	try
	{
		if (!pCritSet)
			return E_INVALIDARG;

		if (!pVal)
			return E_POINTER;

		*pVal = VARIANT_FALSE;

		_bstr_t criterionValue = static_cast<LPCTSTR>(grymEditControl_->EditText);
		pCritSet->PutCriterion(COrgDirectoryCustomController::CriterionName, criterionValue);

		*pVal = VARIANT_TRUE;

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::get_SearchDescription(BSTR * pVal)
{
	try
	{
		if (!pVal)
			return E_POINTER;

		*pVal = NULL;

		std::wstringstream wss_rv;
		wss_rv << OLESTR("<description></description>")
			<< OLESTR("<criterion>")
			<< static_cast<LPCTSTR>(grymEditControl_->EditText)
			<< OLESTR("</criterion>");

		*pVal = _bstr_t(wss_rv.str().c_str()).Detach();

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::get_SearchCaption(BSTR *pVal)
{
	try
	{
		if (!pVal)
			return E_POINTER;

		*pVal = _bstr_t(_T("Пользовательский поиск")).Detach();

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::raw_Clear()
{
	try
	{
		grymEditControl_->EditText = OLESTR("");

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}
