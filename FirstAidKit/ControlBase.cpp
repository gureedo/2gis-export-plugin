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
#include "ControlBase.h"

void ControlBase::SetAccelerator( DWORD accelerator )
{
	accelerator_ = accelerator;
}

HRESULT WINAPI ControlBase::ICommandAcceleratorQIFunc( void *pv, REFIID /*riid*/, LPVOID *ppv, DWORD /*dw*/ )
{
	ControlBase *pThis = static_cast<ControlBase *>(pv);
	*ppv = NULL;
	
	if ( pThis->accelerator_ ) {
		*ppv = static_cast<GrymCore::ICommandAccelerator *>(pThis);
		pThis->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

STDMETHODIMP ControlBase::get_Accelerator( LONG *pVal )
{
	if ( !pVal )
		return E_POINTER;
	*pVal = accelerator_;
	return S_OK;
}