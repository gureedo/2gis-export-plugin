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

#include "stdafx.h"
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>
#include "DlgExport.h"
#include "PluginInfo.h"

using namespace std;

CDlgExport::CDlgExport()
{
	// organizations tables
	m_tables.push_back(new TableInfo(_T("grym_org"), _T("Organization"), false));
	m_tables.push_back(new TableInfo(_T("grym_org_fil"), _T("Organization filials"), true));
	m_tables.push_back(new TableInfo(_T("grym_rub1"), _T("Rubric 1"), false));
	m_tables.push_back(new TableInfo(_T("grym_rub2"), _T("Rubric 2"), false));
	m_tables.push_back(new TableInfo(_T("grym_rub3"), _T("Rubric 3"), false));

	// map tables
	m_tables.push_back(new TableInfo(_T("grym_map_building"), _T("Buildings"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_street"), _T("Streets"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_district"), _T("Disctincts"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_microdistrict"), _T("Microdistincts"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_city"), _T("Cities (secondrary)"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_rwstation"), _T("Railroad stations"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_stationbay"), _T("Station bays"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_territory"), _T("Territories"), false));
	m_tables.push_back(new TableInfo(_T("grym_map_sight"), _T("Sights"), false));

	// common tables
	m_tables.push_back(new TableInfo(_T("grym_city"), _T("Cities (common)"), false));
	m_tables.push_back(new TableInfo(_T("grym_street"), _T("Streets (common)"), false));
	m_tables.push_back(new TableInfo(_T("grym_address"), _T("Address (common)"), false));
}

CDlgExport::~CDlgExport()
{
	m_hWnd = NULL;
}

LRESULT CDlgExport::OnInitDialog( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/ )
{
	m_wndTableList.SubclassWindow(GetDlgItem(IDC_TABLES));

	m_wndTableList.AddColumn(_T("Name"), 0, -1, LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM, LVCFMT_LEFT);
	m_wndTableList.AddColumn(_T("Description"), 1, -1, LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM, LVCFMT_LEFT);
	m_wndTableList.AddColumn(_T("Count"), 2, -1, LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM, LVCFMT_RIGHT);

	LVCOLUMN lvc = { 0 };
	lvc.mask = LVCF_WIDTH;
	lvc.cx = 150;
	m_wndTableList.SetColumn(0, &lvc);
	lvc.cx = 150;
	m_wndTableList.SetColumn(1, &lvc);
	lvc.cx = 100;
	m_wndTableList.SetColumn(2, &lvc);

	for ( auto it = m_tables.cbegin(); it != m_tables.cend(); ++it ) {
		TableInfo *info = *it;

		wstring recCountStr;
		if ( !info->isVirtual ) {
			wstringstream ss;
			GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(_bstr_t(info->name.c_str()));
			ss << table->GetRecordCount();
			recCountStr = ss.str();
		} else {
			recCountStr = _T("0");
		}

		int idx = m_wndTableList.AddItem(0, 0, info->name.c_str());
		m_wndTableList.AddItem(0, 1, info->description.c_str());
		m_wndTableList.AddItem(0, 2, recCountStr.c_str());
		m_wndTableList.SetItemData(idx, (DWORD_PTR)info);
	}

	return TRUE;
}

LRESULT CDlgExport::OnCancel( WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	m_wndTableList.UnsubclassWindow();
	EndDialog(wID);
	return 0;
}

LRESULT CDlgExport::OnSelectExportFolder( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	CFolderDialog dlgFolder;

	if ( dlgFolder.DoModal(*this) == IDOK ) {
		SetDlgItemText(IDC_DSTDIR, dlgFolder.GetFolderPath());
	}

	return 0;
}

LRESULT CDlgExport::OnExport( WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/ )
{
	locale utf8_locale(locale("", locale::ctype), new codecvt_utf8<wchar_t>);

	CString buf;
	GetDlgItemText(IDC_DSTDIR, buf);
	wstring dstDir = buf;

	if ( dstDir.empty() ) {
		MessageBox(_T("Destination folder not selected."));
		return 0;
	}

	if ( *dstDir.rbegin() != _T('\\') )
		dstDir += _T("\\");

	int idx = -1;
	while ( (idx = m_wndTableList.GetNextItem(idx, LVNI_ALL)) != -1 ) {
		if ( !m_wndTableList.GetCheckState(idx) )
			continue;

		TableInfo *info = (TableInfo *)m_wndTableList.GetItemData(idx);
		if ( !info )
			continue;

		m_wndTableList.SelectItem(idx);

		wstring fileName = dstDir + info->name + _T(".csv");
		wofstream csvStream;
		csvStream.open(fileName, ios::out|ios::trunc );
		if ( csvStream.fail() ) {
			wstringstream ss;
			ss << _T("Failed to open \"") << fileName << _T("\" for writing!");
			MessageBox(ss.str().c_str());
			continue;
		}
		csvStream.imbue( utf8_locale );
		
		if ( info->name == _T("grym_org") ) {
			GrymCore::ITablePtr table = g_pi.baseView->Database->GetTable(_bstr_t(info->name.c_str()));
			long count = table->GetRecordCount();
			long i = 0;
		
			csvStream << _T("org_id;org_stable_id;org_name") << endl;

			while ( ++i <= count ) {
				GrymCore::IDataRowPtr row = table->GetRecord(i);

				csvStream << i;
				csvStream << _T(";");
				csvStream << (int)row->GetValue(_bstr_t(OLESTR("stable_id")));
				csvStream << _T(";");
				csvStream << (_bstr_t)row->GetValue(_bstr_t(OLESTR("name")));
				csvStream << endl;
			}
		}

		csvStream.close();

	}

	return 0;
}
