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

#pragma once

#include "GrymApiBase.h"

class ATL_NO_VTABLE CPluginImpl
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IGrymPlugin
	, public GrymCore::IGrymPluginInfo
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
	STDMETHOD(raw_Initialize)( GrymCore::IGrym *pRoot, GrymCore::IBaseViewThread *pBaseView );
	STDMETHOD(raw_Terminate)();

public: // GrymCore::IGrymPluginInfo
	STDMETHOD(get_XMLInfo)( BSTR *pVal );

private:
	// search group stuff
	GrymCore::IStdDirectoryCustomControllerPtr customDirController_;
	GrymCore::ISearchRibbonGroupPtr searchGroup_;
	GrymCore::ISearchGroupControlPtr ctrlSearch_;

	// tools group stuff
	GrymCore::IRibbonGroupPtr toolsGroup_;
	GrymCore::ICommandActionPtr cmdExport_;
};
