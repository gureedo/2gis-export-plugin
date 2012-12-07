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

//////////////////////////////////////////////////////////////////////////
// command
//////////////////////////////////////////////////////////////////////////

class ATL_NO_VTABLE CommandBase
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::ICommandAccelerator
	, public GrymCore::ICommandAction
{
protected:
	CommandBase();
	~CommandBase();

	BEGIN_COM_MAP(CommandBase)
		COM_INTERFACE_ENTRY(GrymCore::ICommandAction)
		COM_INTERFACE_ENTRY_FUNC(__uuidof(GrymCore::ICommandAccelerator), 0, ICommandAcceleratorQIFunc)
	END_COM_MAP()

public: // GrymCore::ICommandAccelerator
	STDMETHOD(get_Accelerator)( LONG *pVal );

public: // GrymCore::ICommandAction
	// pure virtual
	STDMETHOD(raw_OnCommand)(void) PURE;

protected:
	DWORD accelerator_;
private:
	static HRESULT WINAPI ICommandAcceleratorQIFunc(void* pv, REFIID riid, LPVOID* ppv, DWORD dw);
};

//////////////////////////////////////////////////////////////////////////
// control
//////////////////////////////////////////////////////////////////////////

class ATL_NO_VTABLE ControlBase
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IControlPlacement
	, public GrymCore::IControlAppearance
{
protected:
	ControlBase();

	~ControlBase();

	BEGIN_COM_MAP(ControlBase)
		COM_INTERFACE_ENTRY(GrymCore::IControlPlacement)
		COM_INTERFACE_ENTRY(GrymCore::IControlAppearance)
	END_COM_MAP()

public: // GrymCore::IControlPlacement 
	STDMETHOD(get_PlacementCode)(BSTR *pVal);

public: // GrymCore::IControlAppearance
	STDMETHOD(get_Tag)(BSTR *pVal); 
	STDMETHOD(get_Caption)(BSTR *pVal);
	STDMETHOD(get_Description)(BSTR *pVal);
	STDMETHOD(get_Icon)(IUnknown ** pVal);

protected:
	_bstr_t placement_code_;
	_bstr_t tag_, caption_, description_;
	IUnknownPtr icon_;
};

//////////////////////////////////////////////////////////////////////////
// visible command
//////////////////////////////////////////////////////////////////////////

class ATL_NO_VTABLE VisibleCommandBase
	: public CommandBase
	, public GrymCore::IControlPlacement
	, public GrymCore::IControlAppearance
{
protected:
	VisibleCommandBase();

	~VisibleCommandBase();

	BEGIN_COM_MAP(VisibleCommandBase)
		COM_INTERFACE_ENTRY(GrymCore::IControlPlacement)
		COM_INTERFACE_ENTRY(GrymCore::IControlAppearance)
		COM_INTERFACE_ENTRY_CHAIN(CommandBase)
	END_COM_MAP()

public: // GrymCore::IControlPlacement 
	STDMETHOD(get_PlacementCode)(BSTR *pVal);

public: // GrymCore::IControlAppearance
	STDMETHOD(get_Tag)(BSTR *pVal); 
	STDMETHOD(get_Caption)(BSTR *pVal);
	STDMETHOD(get_Description)(BSTR *pVal);
	STDMETHOD(get_Icon)(IUnknown ** pVal);

protected:
	_bstr_t placement_code_;
	_bstr_t tag_, caption_, description_;
	IUnknownPtr icon_;
};

//////////////////////////////////////////////////////////////////////////
// visible command with state
//////////////////////////////////////////////////////////////////////////

#if 0
class ATL_NO_VTABLE VisibleStateCommandBase
	: public VisibleCommandBase
	, public GrymCore::ICommandState
{
protected:
	VisibleStateCommandBase( const _bstr_t &placement_code, const _bstr_t &tag, const _bstr_t &caption, 
		const _bstr_t &description, IUnknown *icon = 0, DWORD accelerator = 0 );

	~VisibleStateCommandBase();

	BEGIN_COM_MAP(VisibleStateCommandBase)
		COM_INTERFACE_ENTRY(GrymCore::IControlState)
		COM_INTERFACE_ENTRY(GrymCore::ICommandState)
		COM_INTERFACE_ENTRY_CHAIN(VisibleCommandBase)
	END_COM_MAP()

public: // GrymCore::ICommandState
	// default implementation: always available
	STDMETHOD(get_Available)(VARIANT_BOOL *pVal);

public: // GrymCore::IControlState
	// default implementation: always enabled
	STDMETHOD(get_Enabled)(VARIANT_BOOL *pVal);
	// default implementation: always not checked
	STDMETHOD(get_Checked)(VARIANT_BOOL *pVal);
};
#endif