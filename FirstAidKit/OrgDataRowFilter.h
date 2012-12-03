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

class ATL_NO_VTABLE COrgDataRowFilter
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IStdDirectoryDataRowFilter
{
public:
	static GrymCore::IStdDirectoryDataRowFilterPtr CreateInstance( const _bstr_t &filter );

	~COrgDataRowFilter() {}

protected:
	COrgDataRowFilter() {}

	BEGIN_COM_MAP(COrgDataRowFilter)
		COM_INTERFACE_ENTRY(GrymCore::IStdDirectoryDataRowFilter)
	END_COM_MAP()

public:	// IStdDirectoryDataRowFilter
	STDMETHOD(raw_Check)( GrymCore::IDataRow *pRecord, VARIANT_BOOL *pVal );

private:
	static const _bstr_t orgFilType_;
	static const _bstr_t orgType_;
	static const _bstr_t nameKey_;
	static const _bstr_t parentKey_;

	_bstr_t filter_;
};
