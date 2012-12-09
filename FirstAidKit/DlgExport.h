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

#include <vector>
#include <string>
#include "resource.h"

class CDlgExport
	: public CDialogImpl<CDlgExport>
{
public:
	CDlgExport();
	virtual ~CDlgExport();

	enum { IDD = IDD_EXPORT };

	BEGIN_MSG_MAP(CDlgExport)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(IDC_BTNSELFOLDER, OnSelectExportFolder)
		COMMAND_ID_HANDLER(IDC_BTNEXPORT, OnExport)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnSelectExportFolder(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnExport(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	struct TableInfo {
		std::wstring name;
		std::wstring description;
		bool isVirtual;
		TableInfo( const std::wstring &name, const std::wstring &description, bool isVirtual )
			: name(name)
			, description(description)
			, isVirtual(isVirtual)
		{
		}
	};

	std::vector<TableInfo*> m_tables;

	CCheckListViewCtrl m_wndTableList;
	CListBox m_wndLog;

	void exportTable( const std::wstring &tableName, const std::wstring &outFile ) const;
};
