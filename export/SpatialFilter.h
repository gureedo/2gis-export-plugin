#pragma once

class ATL_NO_VTABLE CSpatialFilter
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::ISpatialFilter
{
public:
	static GrymCore::ISpatialFilterPtr CreateInstance(GrymCore::IMapRect * bounds);

	~CSpatialFilter(void);

protected:
	CSpatialFilter(void);

	BEGIN_COM_MAP(CSpatialFilter)
		COM_INTERFACE_ENTRY(GrymCore::ISpatialFilter)
	END_COM_MAP()

public:	// ISpatialFilter
	STDMETHOD(raw_Check)(GrymCore::IMapPoint * pPos, VARIANT_BOOL * pVal);
	STDMETHOD(get_Bounds)(GrymCore::IMapRect ** pVal);

private:
	GrymCore::IMapRectPtr bounds_;
};
