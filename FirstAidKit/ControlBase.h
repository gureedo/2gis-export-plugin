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

#include "ControlAppearanceBase.h"

class ATL_NO_VTABLE ControlBase
	: public ControlAppearanceBase
	, public GrymCore::ICommandAction
	, public GrymCore::ICommandAccelerator
{
protected:
	ControlBase() : accelerator_(0) {}
	~ControlBase() {}

	BEGIN_COM_MAP(ControlBase)
		COM_INTERFACE_ENTRY(GrymCore::ICommandAction)
		COM_INTERFACE_ENTRY_FUNC(__uuidof(GrymCore::ICommandAccelerator), 0, ICommandAcceleratorQIFunc)
		COM_INTERFACE_ENTRY_CHAIN(ControlAppearanceBase)
	END_COM_MAP()

	void SetAccelerator( DWORD accelerator );

public: //ICommandAction
	STDMETHOD(raw_OnCommand)(void) PURE;

public: //ICommandAccelerator
	STDMETHOD(get_Accelerator)(LONG * pVal);

protected:
	DWORD accelerator_;

private:
	static HRESULT WINAPI ICommandAcceleratorQIFunc( void *pv, REFIID riid, LPVOID *ppv, DWORD dw );
};