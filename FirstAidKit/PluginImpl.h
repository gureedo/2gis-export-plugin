#pragma once

class ATL_NO_VTABLE CPluginImpl : 
	public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>,
	public GrymCore::IGrymPlugin,
	public GrymCore::IGrymPluginInfo
{
public:
	static GrymCore::IGrymPluginPtr CreateInstance();
protected:
	CPluginImpl() {}

	BEGIN_COM_MAP(CPluginImpl)
		COM_INTERFACE_ENTRY(GrymCore::IGrymPlugin)
		COM_INTERFACE_ENTRY(GrymCore::IGrymPluginInfo)
	END_COM_MAP()

public: // GrymCore::IGrymPlugin
	STDMETHOD(raw_Initialize)(GrymCore::IGrym *pRoot, GrymCore::IBaseViewThread *pBaseView);
	STDMETHOD(raw_Terminate)();

public: // GrymCore::IGrymPluginInfo
	STDMETHOD(get_XMLInfo)(BSTR *pVal);

private:
	GrymCore::IGrymPtr grymAppPtr_;
	GrymCore::IBaseViewThreadPtr baseViewPtr_;
	GrymCore::IStdDirectoryCustomControllerPtr customDirController_;
	GrymCore::ISearchRibbonGroupPtr searchGroup_;
	GrymCore::ISearchGroupControlPtr searchControl_;
};
