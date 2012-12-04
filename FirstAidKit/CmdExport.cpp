#include "stdafx.h"
#include "Util.h"
#include "CmdExport.h"

GrymCore::ICommandActionPtr CCmdExport::CreateInstance( const CPluginInfo &pi )
{
	ATL::CComObject<CCmdExport> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<CCmdExport>::CreateInstance(&obj));
	GrymCore::ICommandActionPtr rv = obj;
	ATLASSERT(NULL != rv);

	return rv;
}

static const _bstr_t tag = OLESTR("FirstAidKit.MainTab.ExportButton");
static const _bstr_t placement_code = OLESTR("1000ExportButton:0");
static const _bstr_t caption = OLESTR("Export");
static const _bstr_t description = OLESTR("DESCRIPTION");
//static IUnknownPtr icon;

CCmdExport::CCmdExport()
	: VisibleCommandBase(placement_code, tag, caption ,description)
{
	//icon_ = Util::LoadResourceRaster()
}

CCmdExport::~CCmdExport()
{
}

STDMETHODIMP CCmdExport::raw_OnCommand()
{
	try {
		// do stuff here
	} catch (...) {
	}

	return S_OK;
}
