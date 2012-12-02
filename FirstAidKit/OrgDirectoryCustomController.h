#pragma once

class ATL_NO_VTABLE COrgDirectoryCustomController
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IStdDirectoryCustomController
	, public GrymCore::IStdDirectoryCustomFilterController
{
public:
	static GrymCore::IStdDirectoryCustomControllerPtr CreateInstance();

	~COrgDirectoryCustomController(void);

protected:
	COrgDirectoryCustomController(void);

	BEGIN_COM_MAP(COrgDirectoryCustomController)
		COM_INTERFACE_ENTRY(GrymCore::IStdDirectoryCustomController)
		COM_INTERFACE_ENTRY(GrymCore::IStdDirectoryCustomFilterController)
	END_COM_MAP()

public:	// IStdDirectoryCustomController
	STDMETHOD(raw_MakeCellController)(GrymCore::IStdDirectoryCellInfo * pVal,
		GrymCore::IStdDirectoryCellCustomController ** pPersonalController);

public:	// IStdDirectoryCustomFilterController
	STDMETHOD(raw_CustomizeQuery)(GrymCore::IDirectoryCriteriaHelper * pCriterion,
		GrymCore::IStdDirectoryQueryCustomize * pQuery);

public:
	// имя нашего пользовательского критерия,
	// который будем использовать для поиска
	static const _bstr_t CriterionName;
};
