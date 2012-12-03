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

class ATL_NO_VTABLE ControlAppearanceBase
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IControlPlacement
	, public GrymCore::IControlAppearance
{
protected:
	ControlAppearanceBase() {}
	~ControlAppearanceBase() {}

	void SetAppearance( const _bstr_t &tag, const _bstr_t &caption, const _bstr_t &description = _T(""), IUnknown *icon = NULL );
	void SetPlacement( const _bstr_t &placement_code );

	BEGIN_COM_MAP(ControlAppearanceBase)
		COM_INTERFACE_ENTRY(GrymCore::IControlPlacement)
		COM_INTERFACE_ENTRY(GrymCore::IControlAppearance)
	END_COM_MAP()

public: // GrymCore::IControlPlacement 
	STDMETHOD(get_PlacementCode)( BSTR *pVal );

public: // GrymCore::IControlAppearance
	STDMETHOD(get_Tag)( BSTR *pVal );
	STDMETHOD(get_Caption)( BSTR *pVal );
	STDMETHOD(get_Description)( BSTR *pVal );
	STDMETHOD(get_Icon)( IUnknown **pVal );

protected:
	_bstr_t placement_code_;
	_bstr_t tag_;
	_bstr_t caption_;
	_bstr_t description_;
	IUnknownPtr icon_;
};