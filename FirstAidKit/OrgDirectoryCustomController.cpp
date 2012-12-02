#include "StdAfx.h"
#include "OrgDirectoryCustomController.h"
#include "OrgDataRowFilter.h"

const _bstr_t COrgDirectoryCustomController::CriterionName = OLESTR("fak_org_search");

COrgDirectoryCustomController::COrgDirectoryCustomController(void)
{
}

COrgDirectoryCustomController::~COrgDirectoryCustomController(void)
{
}

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
	GrymCore::IDirectoryCriteriaHelper * pCriterion,
	GrymCore::IStdDirectoryQueryCustomize * pQuery)
{
	try
	{
		if (!pCriterion || !pQuery)
			return E_INVALIDARG;

		if (pCriterion->GetExists(CriterionName))
		{
			_bstr_t criterionValue = pCriterion->GetCriterion(CriterionName);
			pQuery->AddFilter(COrgDataRowFilter::CreateInstance(criterionValue));
		}

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}
