#include "stdafx.h"
#include "resource.h"
#include "PluginImpl.h"

class CFirstAidKitModule : public CAtlDllModuleT< CFirstAidKitModule > {};
CFirstAidKitModule _AtlModule;

extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(hInstance);
	return _AtlModule.DllMain(dwReason, lpReserved); 
}

extern "C" int __stdcall CreateGrymPlugin( IUnknown **pPlugin )
{
	GrymCore::IGrymPluginPtr plugin = CPluginImpl::CreateInstance();
	if ( NULL == plugin ) {
		return 1;
	}
	*pPlugin = IUnknownPtr(plugin).Detach();
	return 0;
}
