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

#include "stdafx.h"
#include "resource.h"
#include "Util.h"
#include "CmdExport.h"
#include "DlgExport.h"
#include "PluginInfo.h"

GrymCore::ICommandActionPtr CCmdExport::CreateInstance()
{
	ATL::CComObject<CCmdExport> *obj;
	ATLVERIFY(S_OK == ATL::CComObject<CCmdExport>::CreateInstance(&obj));
	GrymCore::ICommandActionPtr rv = obj;
	ATLASSERT(NULL != rv);

	obj->tag_ = OLESTR("Export.MainTab.ToolsGroup.CmdExport");
	obj->placement_code_ = OLESTR("0001CmdExport:0");
	obj->caption_ = OLESTR("Export");
	obj->description_ = OLESTR("DESCRIPTION");
	obj->icon_ = Util::LoadResourceRaster(g_pi.baseView->Factory, IDB_EXPORT);

	return rv;
}

CCmdExport::CCmdExport()
{
}

CCmdExport::~CCmdExport()
{
}

STDMETHODIMP CCmdExport::raw_OnCommand()
{
	try {
		CDlgExport dlg;
		
		dlg.DoModal();

		return S_OK;
	} catch (...) {
	}

	return E_FAIL;
}
