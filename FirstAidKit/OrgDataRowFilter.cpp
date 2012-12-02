#include "StdAfx.h"
#include "OrgDataRowFilter.h"
#include "Wildcard.h"

const _bstr_t COrgDataRowFilter::orgFilType_ = OLESTR("grym_org_fil");
const _bstr_t COrgDataRowFilter::orgType_ = OLESTR("grym_org");
const _bstr_t COrgDataRowFilter::nameKey_ = OLESTR("name");
const _bstr_t COrgDataRowFilter::parentKey_ = OLESTR("parent");

COrgDataRowFilter::COrgDataRowFilter(void)
{
}

COrgDataRowFilter::~COrgDataRowFilter(void)
{
}

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
	try
	{
		if (!pRecord)
			return E_INVALIDARG;

		if (!pVal)
			return E_POINTER;

		*pVal = VARIANT_FALSE;

		_bstr_t orgName;
		if ( pRecord->Type == orgFilType_ )
		{
			// если передан филиал, то нужно у него запросить его организацию, чтобы получить ее название.
			if (GrymCore::IDataRowPtr org = pRecord->GetValue(parentKey_))
			{
				// получаем название организации
				orgName = org->GetValue(nameKey_);
			}
		}
		else if ( pRecord->Type == orgType_ )
		{
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
	} catch (...) { }
	return E_FAIL;
}
