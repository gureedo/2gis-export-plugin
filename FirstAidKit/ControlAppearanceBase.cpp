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

#include "StdAfx.h"
#include "ControlAppearanceBase.h"

void ControlAppearanceBase::SetAppearance( const _bstr_t &tag, const _bstr_t &caption, const _bstr_t &description, IUnknown *icon )
{
	tag_ = tag;
	caption_ = caption;
	description_ = description;
	icon_ = icon;
}

void ControlAppearanceBase::SetPlacement( const _bstr_t &placement_code )
{
	placement_code_ = placement_code;
}

STDMETHODIMP ControlAppearanceBase::get_PlacementCode( BSTR *pVal )
{
	if ( !pVal )
		return E_POINTER;
	*pVal = placement_code_.copy();
	return S_OK;
}

STDMETHODIMP ControlAppearanceBase::get_Tag( BSTR *pVal )
{
	if ( !pVal )
		return E_POINTER;
	*pVal = tag_.copy();
	return S_OK;
}

STDMETHODIMP ControlAppearanceBase::get_Caption( BSTR *pVal )
{
	if ( !pVal )
		return E_POINTER;
	*pVal = caption_.copy();
	return S_OK;
}

STDMETHODIMP ControlAppearanceBase::get_Description( BSTR *pVal )
{
	if ( !pVal )
		return E_POINTER;
	*pVal = description_.copy();
	return S_OK;
}

STDMETHODIMP ControlAppearanceBase::get_Icon( IUnknown **pVal )
{
	if ( !pVal )
		return E_POINTER;
	*pVal = IUnknownPtr(icon_).Detach();
	return S_OK;
}