#pragma once

class ATL_NO_VTABLE COrgDataRowFilter
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IStdDirectoryDataRowFilter
{
public:
	static GrymCore::IStdDirectoryDataRowFilterPtr CreateInstance(const _bstr_t & postfix);

	~COrgDataRowFilter(void);

protected:
	COrgDataRowFilter(void);

	BEGIN_COM_MAP(COrgDataRowFilter)
		COM_INTERFACE_ENTRY(GrymCore::IStdDirectoryDataRowFilter)
	END_COM_MAP()

public:	// IStdDirectoryDataRowFilter
	STDMETHOD(raw_Check)(GrymCore::IDataRow * pRecord, VARIANT_BOOL * pVal);

private:
	static const _bstr_t orgFilType_;
	static const _bstr_t orgType_;
	static const _bstr_t nameKey_;
	static const _bstr_t parentKey_;

	_bstr_t filter_;
};
