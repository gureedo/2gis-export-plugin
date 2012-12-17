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

class ATL_NO_VTABLE CExtendedInfoBlock
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IMapInfoController
{
public:
	static GrymCore::IMapInfoControllerPtr CreateInstance();

	~CExtendedInfoBlock() {}

protected:
	CExtendedInfoBlock() {}

	BEGIN_COM_MAP(CExtendedInfoBlock)
		COM_INTERFACE_ENTRY(GrymCore::IMapInfoController)
	END_COM_MAP()

public:	// IMapInfoController
	STDMETHOD(raw_Check)( GrymCore::IFeature *pFeature, VARIANT_BOOL *pVal );
	STDMETHOD(get_Title)( BSTR *pVal );
	STDMETHOD(raw_Fill)( GrymCore::IFeature *pFeature, GrymCore::ICalloutTab *pTab );
	STDMETHOD(raw_OnTabAction)( GrymCore::ICalloutTab *pTab, BSTR bsActionID );
};