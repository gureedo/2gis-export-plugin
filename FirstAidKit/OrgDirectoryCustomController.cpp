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
#include "OrgDirectoryCustomController.h"
#include "OrgDataRowFilter.h"

const _bstr_t COrgDirectoryCustomController::CriterionName = OLESTR("fak_org_search");

GrymCore::IStdDirectoryCustomControllerPtr COrgDirectoryCustomController::CreateInstance()
{
	ATL::CComObject<COrgDirectoryCustomController> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<COrgDirectoryCustomController>::CreateInstance(&obj));
	GrymCore::IStdDirectoryCustomControllerPtr rv = obj;
	ATLASSERT(NULL != rv);

	return rv;
}

STDMETHODIMP COrgDirectoryCustomController::raw_MakeCellController(
	GrymCore::IStdDirectoryCellInfo * /*pVal*/,
	GrymCore::IStdDirectoryCellCustomController ** /*pPersonalController*/)
{
	return S_FALSE;
}

STDMETHODIMP COrgDirectoryCustomController::raw_CustomizeQuery(
	GrymCore::IDirectoryCriteriaHelper *pCriterion,
	GrymCore::IStdDirectoryQueryCustomize *pQuery)
{
	try {
		if ( !pCriterion || !pQuery )
			return E_INVALIDARG;

		if ( pCriterion->GetExists(CriterionName) ) {
			_bstr_t criterionValue = pCriterion->GetCriterion(CriterionName);
			pQuery->AddFilter(COrgDataRowFilter::CreateInstance(criterionValue));
		}

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}
