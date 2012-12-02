#include "StdAfx.h"
#include "MenuCommand.h"

GrymCore::ICommandActionPtr MenuCommand::CreateInstance(const ControlAppearanceParams &appearance, DWORD accelerator)
{
	ATL::CComObject<MenuCommand> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<MenuCommand>::CreateInstance(&obj));
	GrymCore::ICommandActionPtr rv = obj;
	ATLASSERT(NULL != rv);

	obj->SetPlacement(appearance.placement_code);
	obj->SetAppearance(appearance.tag, appearance.caption, appearance.description, appearance.icon);
	obj->SetAccelerator(accelerator);

	return rv;
}