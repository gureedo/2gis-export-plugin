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

class ATL_NO_VTABLE COrgDirectoryCustomController
	: public ATL::CComObjectRootEx<ATL::CComSingleThreadModel>
	, public GrymCore::IStdDirectoryCustomController
	, public GrymCore::IStdDirectoryCustomFilterController
{
public:
	static GrymCore::IStdDirectoryCustomControllerPtr CreateInstance();

	~COrgDirectoryCustomController() {}

protected:
	COrgDirectoryCustomController() {}

	BEGIN_COM_MAP(COrgDirectoryCustomController)
		COM_INTERFACE_ENTRY(GrymCore::IStdDirectoryCustomController)
		COM_INTERFACE_ENTRY(GrymCore::IStdDirectoryCustomFilterController)
	END_COM_MAP()

public:	// IStdDirectoryCustomController
	STDMETHOD(raw_MakeCellController)( GrymCore::IStdDirectoryCellInfo *pVal,
		GrymCore::IStdDirectoryCellCustomController ** pPersonalController );

public:	// IStdDirectoryCustomFilterController
	STDMETHOD(raw_CustomizeQuery)( GrymCore::IDirectoryCriteriaHelper *pCriterion,
		GrymCore::IStdDirectoryQueryCustomize *pQuery );

public:
	static const _bstr_t CriterionName;
};
