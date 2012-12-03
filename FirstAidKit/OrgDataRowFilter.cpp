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
#include "Wildcard.h"
#include "OrgDataRowFilter.h"

const _bstr_t COrgDataRowFilter::orgFilType_ = OLESTR("grym_org_fil");
const _bstr_t COrgDataRowFilter::orgType_ = OLESTR("grym_org");
const _bstr_t COrgDataRowFilter::nameKey_ = OLESTR("name");
const _bstr_t COrgDataRowFilter::parentKey_ = OLESTR("parent");

GrymCore::IStdDirectoryDataRowFilterPtr COrgDataRowFilter::CreateInstance( const _bstr_t &filter )
{
	ATL::CComObject<COrgDataRowFilter> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<COrgDataRowFilter>::CreateInstance(&obj));
	GrymCore::IStdDirectoryDataRowFilterPtr rv = obj;
	ATLASSERT(NULL != rv);

	obj->filter_ = filter;

	return rv;
}

STDMETHODIMP COrgDataRowFilter::raw_Check( GrymCore::IDataRow *pRecord, VARIANT_BOOL *pVal )
{
	try {
		if ( !pRecord )
			return E_INVALIDARG;

		if ( !pVal )
			return E_POINTER;

		*pVal = VARIANT_FALSE;

		_bstr_t orgName;
		if ( pRecord->Type == orgFilType_ ) {
			// если передан филиал, то нужно у него запросить его организацию, чтобы получить ее название.
			if ( GrymCore::IDataRowPtr org = pRecord->GetValue(parentKey_) ) {
				// получаем название организации
				orgName = org->GetValue(nameKey_);
			}
		} else if ( pRecord->Type == orgType_ ) {
			// получаем название организации
			orgName = pRecord->GetValue(nameKey_);
		} else {
			return S_OK;
		}

		wchar_t *orgNameBuf = _wcsdup(orgName);
		CharLowerW(orgNameBuf);
		if ( Wildcard::wildcardfit(filter_, orgNameBuf) )
		{
			*pVal = VARIANT_TRUE;
		}
		free(orgNameBuf);

		return S_OK;
	} catch (...) {
	}
	
	return E_FAIL;
}
