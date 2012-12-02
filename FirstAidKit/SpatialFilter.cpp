#include "StdAfx.h"
#include "SpatialFilter.h"

CSpatialFilter::CSpatialFilter(void)
{
}

CSpatialFilter::~CSpatialFilter(void)
{
}

GrymCore::ISpatialFilterPtr CSpatialFilter::CreateInstance(GrymCore::IMapRect * bounds)
{
	ATL::CComObject<CSpatialFilter> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<CSpatialFilter>::CreateInstance(&obj));
	GrymCore::ISpatialFilterPtr rv = obj;
	ATLASSERT(NULL != rv);

	obj->bounds_ = bounds;

	return rv;
}

STDMETHODIMP CSpatialFilter::raw_Check(GrymCore::IMapPoint * pPos, VARIANT_BOOL * pVal)
{
	try
	{
		if (!pPos)
			return E_INVALIDARG;

		if (!pVal)
			return E_POINTER;

		*pVal = VARIANT_FALSE;

		if (pPos->X >= bounds_->MinX && bounds_->MaxX >= pPos->X &&
			pPos->Y >= bounds_->MinY && bounds_->MaxY >= pPos->Y)
			*pVal = VARIANT_TRUE;

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}

STDMETHODIMP CSpatialFilter::get_Bounds(GrymCore::IMapRect ** pVal)
{
	try
	{
		if (!pVal)
			return E_POINTER;

		*pVal = GrymCore::IMapRectPtr(bounds_).Detach();

		return S_OK;
	} catch (...) { }
	return E_FAIL;
}
