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

class ATL_NO_VTABLE COrgSearchControl
	: public ControlBase
	, public GrymCore::IContainerControl
	, public GrymCore::ISearchGroupControl
{
public:
	static GrymCore::ISearchGroupControlPtr CreateInstance( const CPluginInfo &pi );

	~COrgSearchControl();

protected:
	COrgSearchControl();

	BEGIN_COM_MAP(COrgSearchControl)
		COM_INTERFACE_ENTRY(GrymCore::IContainerControl)
		COM_INTERFACE_ENTRY(GrymCore::ISearchGroupControl)
		COM_INTERFACE_ENTRY_CHAIN(ControlBase)
	END_COM_MAP()

public:	//IContainerControl
	STDMETHOD(get_InternalControl)( IUnknown **pVal );

public:	//ISearchGroupControl
	STDMETHOD(get_SearchEnabled)( VARIANT_BOOL *pVal );
	STDMETHOD(get_ClearEnabled)( VARIANT_BOOL *pVal );
	STDMETHOD(raw_FillCriteriaSet)( GrymCore::ICriteriaSet *pCritSet, VARIANT_BOOL *pVal );
	STDMETHOD(get_SearchDescription)( BSTR *pVal );
	STDMETHOD(get_SearchCaption)( BSTR *pVal );
	STDMETHOD(raw_Clear)();

private:
	void AdjustEditControl( const GrymCore::IGrymObjectFactory2Ptr &factory );

private:
	// Встроенный элемент управления "поле ввода"
	GrymCore::IGrymControlEditTextHolderPtr grymEditControl_;
};
