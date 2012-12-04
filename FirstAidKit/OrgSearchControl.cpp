// Copyright (C) 2012 gureedo
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "StdAfx.h"
#include <sstream>
#include "OrgSearchControl.h"
#include "OrgDirectoryCustomController.h"

GrymCore::ISearchGroupControlPtr COrgSearchControl::CreateInstance(	const CPluginInfo &pi )
{
	ATL::CComObject<COrgSearchControl> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<COrgSearchControl>::CreateInstance(&obj));
	GrymCore::ISearchGroupControlPtr rv = obj;
	ATLASSERT(NULL != rv);

	obj->AdjustEditControl(pi.baseView->Factory);

	return rv;
}

static const _bstr_t empty_bstr = OLESTR("");
static const _bstr_t tag = OLESTR("FirstAidKit.MainTab.SearchControl");
static const _bstr_t placement_code =
	OLESTR("<control_pos>")
	OLESTR("<size min_width=\"150\" max_width=\"300\" height_in_rows=\"1\" />") 
	OLESTR("<position column_id=\"100SearchGroup\" row_id=\"500MyRowByID\" order_in_row=\"1\" />")
	OLESTR("</control_pos>");

COrgSearchControl::COrgSearchControl()
	: ControlBase(placement_code, tag, empty_bstr, empty_bstr)
{
}

COrgSearchControl::~COrgSearchControl()
{
}

void COrgSearchControl::AdjustEditControl( const GrymCore::IGrymObjectFactory2Ptr &factory )
{
	grymEditControl_ = factory->CreateGrymControl(GrymCore::GrymControlTypeEdit);
	GrymCore::IGrymControlPtr grymControl = grymEditControl_;
	grymControl->Style = GrymCore::GrymControlStyleCaption;
	grymControl->Width = 170;
	grymControl->Height = 25;
}

STDMETHODIMP COrgSearchControl::get_InternalControl( IUnknown **pVal )
{
	try {
		if ( !pVal )
			return E_POINTER;

		*pVal = IUnknownPtr(grymEditControl_).Detach();

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::get_SearchEnabled( VARIANT_BOOL *pVal )
{
	try {
		if ( !pVal )
			return E_POINTER;

		*pVal = (grymEditControl_->EditText.length() != 0) ? VARIANT_TRUE : VARIANT_FALSE;

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::get_ClearEnabled( VARIANT_BOOL *pVal )
{
	return get_SearchEnabled(pVal);
}

STDMETHODIMP COrgSearchControl::raw_FillCriteriaSet( GrymCore::ICriteriaSet *pCritSet, VARIANT_BOOL *pVal )
{
	try {
		if ( !pCritSet )
			return E_INVALIDARG;

		if ( !pVal )
			return E_POINTER;

		*pVal = VARIANT_FALSE;

		_bstr_t criterionValue = static_cast<LPCTSTR>(grymEditControl_->EditText);
		pCritSet->PutCriterion(COrgDirectoryCustomController::CriterionName, criterionValue);

		*pVal = VARIANT_TRUE;

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::get_SearchDescription( BSTR *pVal )
{
	try {
		if ( !pVal )
			return E_POINTER;

		*pVal = NULL;

		std::wstringstream wss_rv;
		wss_rv << OLESTR("<description></description>")
			<< OLESTR("<criterion>")
			<< static_cast<LPCTSTR>(grymEditControl_->EditText)
			<< OLESTR("</criterion>");

		*pVal = _bstr_t(wss_rv.str().c_str()).Detach();

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::get_SearchCaption( BSTR *pVal )
{
	try {
		if ( !pVal )
			return E_POINTER;

		*pVal = _bstr_t(_T("User search")).Detach();

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}

STDMETHODIMP COrgSearchControl::raw_Clear()
{
	try {
		grymEditControl_->EditText = OLESTR("");

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}
